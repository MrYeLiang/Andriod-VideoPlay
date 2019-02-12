//
// Created by 叶亮 on 2019/1/27.
//

#include "FFDemux.h"
#include "Xlog.h"

extern "C"{
#include <libavformat/avformat.h>
}

//打开文件 或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url)
{
    XLOGI("Open file %s begin", url);

    int re = avformat_open_input(&ic, url, 0, 0);

    if(re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDemux open %s failed!", url);
        return false;
    }
    XLOGI("FFDemux open %s success!", url);

    //读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if(re != 0 ){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("avformat_find_stream_info %s failed!", url);
        return false;
    }
    this->totalMs = ic->duration/(AV_TIME_BASE/1000);
    XLOGI("total ms = %d!", totalMs);
    return true;
}

//获取视频参数
XParameter FFDemux::GetVPara()
{
    if(!ic){
        XLOGE("GetVPara failed! ic is NULL! ");
        return XParameter();
    }

    //获取了视频流索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if(re < 0){
        XLOGE("av_find_best_stream failed!");
        return XParameter();
    }
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    return para;
}

//读取一帧数据，数据由调用者清理
XData FFDemux::Read()
{
    if(!ic){
        return XData();
    }
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if(re != 0){
        av_packet_free(&pkt);
        return XData();
    }
    d.data = (unsigned char*)pkt;
    d.size = pkt->size;

    return d;
}

FFDemux::FFDemux()
{
    static bool isFirst = true;
    if(isFirst)
    {
        isFirst = false;
        //注册所有封装器
        av_register_all();
        //注册所有的解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg!");
    }
}