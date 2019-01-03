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


//pts 显示时间   dts解码时间

static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? (double) 0 : r.num / (double) r.den;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_pracitce_videoplay_MainActivity_open(JNIEnv *env,
                                              jobject instance, jstring url_) {

    const char *path = env->GetStringUTFChars(url_, 0);

    //1 初始化解封装
    av_register_all();

    AVFormatContext *ic = NULL;

    //2 打开文件
    int re = avformat_open_input(&ic, path, 0, 0);

    if (re == 0) {
        LOGEW("avformat_open_input %s success!", path);
    } else {
        LOGEW("avformat_open_input %s failed!: %s", av_err2str(re));
    }

    //3 获取流信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        LOGEW("avformat_find_stream_info failed!");
    }
    LOGEW("duration = %lld nb_streams = %d", ic->duration, ic->nb_streams);

    int fps = 0;
    int videoStream = 0;
    int audioStream = 1;

    //4 获取视频音频流位置
    for (int i = 0; i < ic->nb_streams; i++) {
        AVStream *as = ic->streams[i];
        if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            LOGEW("视频数据");
            videoStream = i;
            fps = r2d(as->avg_frame_rate);

            LOGEW("fps = %d, width = %d height = %d codeid = %d pixformat = %d", fps,
                  as->codecpar->width,
                  as->codecpar->height,
                  as->codecpar->codec_id,
                  as->codecpar->format);

        } else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            LOGEW("音频数据");
            audioStream = i;
            LOGEW("sample_rate = %d channels = %d sample_format = %d",
                  as->codecpar->sample_rate,
                  as->codecpar->channels,
                  as->codecpar->format);
        }
    }

    //5 获取音频流信息
    audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    LOGEW("av_find_best_stream audioStream %d", audioStream);

    //==================================== 视频解码器 ================================================
    //1 软解码器
    AVCodec *vcodec = avcodec_find_decoder(ic->streams[videoStream]->codecpar->codec_id);

    //硬解码
    //codec = avcodec_find_decoder_by_name("h264_mediacodec");

    if (!vcodec) {
        LOGEW("avcodec_find failed");
    }

    //2 解码器初始化
    AVCodecContext *vc = avcodec_alloc_context3(vcodec);

    //3 解码器参数赋值
    avcodec_parameters_to_context(vc, ic->streams[videoStream]->codecpar);

    vc->thread_count = 1;

    //4 打开解码器
    re = avcodec_open2(vc, 0, 0);
    LOGEW("vc timebase = %d/ %d", vc->time_base.num, vc->time_base.den);

    if (re != 0) {
        LOGEW("avcodec_open2 video failed!");
    }

    //==================================== 音频解码器 ================================================
    //1 软解码器
    AVCodec *acodec = avcodec_find_decoder(ic->streams[audioStream]->codecpar->codec_id);

    if (!acodec) {
        LOGEW("avcodec_find failed!");
    }

    //2 解码器初始化
    AVCodecContext *ac = avcodec_alloc_context3(acodec);
    avcodec_parameters_to_context(ac, ic->streams[audioStream]->codecpar);
    ac->thread_count = 1;

    //3 打开解码器
    re = avcodec_open2(ac, 0, 0);
    if (re != 0) {
        LOGEW("avcodec_open2 audio failed!");
    }

    //4 读取帧数据
    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();

    for (;;) {
        int re = av_read_frame(ic, pkt);
        if (re != 0) {
            LOGEW("读取到结尾处！");
            int pos = 20 * r2d(ic->streams[videoStream]->time_base);
            av_seek_frame(ic, videoStream, pos, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
            break;
        }

        AVCodecContext *cc = vc;
        if (pkt->stream_index == audioStream) {
            cc = ac;
        }

        //发送到线程中解码
        re = avcodec_send_packet(cc, pkt);

        //清理
        int p = pkt->pts;
        av_packet_unref(pkt);

        if (re != 0) {
            LOGEW("avcodec_send_packet failed!");
            continue;
        }

        for (;;) {
            re = avcodec_receive_frame(cc, frame);
            if (re != 0) {
                break;
            }
            LOGEW("avcodec_receive_frame %lld", frame->pts);
        }
    }


    avformat_close_input(&ic);
}