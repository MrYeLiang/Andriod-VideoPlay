//
// Created by 叶亮 on 2019/1/2.
//
#include <jni.h>
#include <string>
#include <android/log.h>

#define  LOGEW(...) __android_log_print(ANDROID_LOG_WARN, "test",__VA_ARGS__)


extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}


static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? (double)0 : r.num/(double)r.den;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_pracitce_videoplay_MainActivity_open(JNIEnv *env,
jobject instance, jstring url_) {

    const  char *path = env->GetStringUTFChars(url_, 0);

    //初始化解封装
    av_register_all();

    AVFormatContext *ic = NULL;

    int re = avformat_open_input(&ic, path, 0, 0);

    if(re == 0){
        LOGEW("avformat_open_input %s success!", path);
    }else{
        LOGEW("avformat_open_input %s failed!: %s",av_err2str(re));
    }

    //获取流信息
    re = avformat_find_stream_info(ic,0);
    if(re != 0){
        LOGEW("avformat_find_stream_info failed!");
    }
    LOGEW("duration = %lld nb_streams = %d",ic->duration,ic->nb_streams);

    int fps = 0;
    int videoStream = 0;
    int audioStream = 1;

    for(int i = 0; i < ic->nb_streams; i++)
    {
        AVStream *as = ic->streams[i];
        if(as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO){
            LOGEW("视频数据");
            videoStream = i;
            fps = r2d(as->avg_frame_rate);

            LOGEW("fps = %d, width = %d height = %d codeid = %d pixformat = %d",
                  fps,as->codecpar->width, as->codecpar->height,as->codecpar->codec_id,as->codecpar->format);
        }else if(as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            LOGEW("音频数据");
            audioStream = i;
            LOGEW("sample_rate = %d channels = %d sample_format = %d",as->codecpar->sample_rate, as->codecpar->channels,as->codecpar->format);

        }
    }

    avformat_close_input(&ic);
}