//
// Created by 叶亮 on 2019/1/25.
//

#include <jni.h>
#include "FFDemux.h"
#include "IObserver.h"
#include "IDecode.h"
#include "FFDecode.h"
#include <unistd.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"

IVideoView *   view = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_decode(JNIEnv *env, jobject instance) {

}

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res)
{
    FFDecode::InitHard(vm);
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    //解封装对象
    IDemux *demux = new FFDemux();

    //音频解码器
    IDecode *aDecode = new FFDecode();
    IResample *resample = new FFResample(); //音频重采样
    aDecode->AddObs(resample);
    demux->AddObs(aDecode);

    IAudioPlay *audioPlay = new SLAudioPlay();
    resample->AddObs(audioPlay);

    //视频解码器
    IDecode *vdecode = new FFDecode();
    view = new GLVideoView();
    vdecode->AddObs(view);
    demux->AddObs(vdecode);

    IPlayer::Get()->demux = demux;
    IPlayer::Get()->adecode = aDecode;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = audioPlay;

    IPlayer::Get()->Open("/storage/emulated/0/video.mp4");
    IPlayer::Get()->Start();

    //视频显示
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    IPlayer::Get()->InitView(win);
}