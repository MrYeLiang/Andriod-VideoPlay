//
// Created by 叶亮 on 2019/2/12.
//

extern "C"
{
#include <libavcodec/avcodec.h>
}

#include "FFDecode.h"
#include "Xlog.h"

bool FFDecode::Open(XParameter para)
{
    if(!para.para){
        return false;
    }
    AVCodecParameters *p = para.para;

    //1查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);

    if(!cd){
        XLOGE("avcodec_find_decoder %d failed", p->codec_id);
        return false;
    }

    XLOGI("avcodec_find_decoder success!");

    //2 创建解码上下文 并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);


    //3 打开解码器
    int re = avcodec_open2(codec, 0, 0);
    if(re != 0){
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf)-1);
        XLOGE("%s", buf);
        return false;
    }

    if(codec->codec_type == AVMEDIA_TYPE_VIDEO){
        this->isAudio = false;
    }else{
        this->isAudio = true;
    }

    XLOGI("avcodec_open2 success!");
    return true;

}

bool FFDecode::SendPacket(XData pkt)
{
    if(pkt.size <= 0 || !pkt.data){
        return false;
    }

    if(!codec){
        return false;
    }

    int re = avcodec_send_packet(codec, (AVPacket *)pkt.data);
    if(re != 0){
        return false;
    }

    return true;
}

//从线程中获取解码结果
XData FFDecode::RecvFrame()
{
    if(!codec){
        return XData();
    }
    if(!frame){
        frame = av_frame_alloc();
    }

    int re = avcodec_receive_frame(codec,frame);
    if(re != 0){
        return XData();
    }
    XData d;
    d.data = (unsigned char *)frame;
    if(codec->codec_type == AVMEDIA_TYPE_VIDEO){
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2])*frame->height;
        d.width = frame->width;
        d.height = frame->height;
    }else
    {
        //样本字节数 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat)frame->format)*frame->nb_samples*2;
    }
    memcpy(d.datas, frame->data, sizeof(d.datas));
    return d;
}