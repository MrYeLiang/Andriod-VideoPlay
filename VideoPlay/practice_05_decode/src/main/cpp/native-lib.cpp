//
// Created by 叶亮 on 2019/1/25.
//

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
#include "FFPlayerBuilder.h"
#include "IPlayerProxy.h"

static IPlayer *player = NULL;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res)
{
    FFPlayerBuilder::InitHard(vm);

   /* player = FFPlayerBuilder::Get()->BuilderPlayer();
    player->Open("/storage/emulated/0/video.mp4");
    player->Start();*/

    IPlayerProxy::Get()->Init(vm);
    IPlayerProxy::Get()->Open("/storage/emulated/0/video.mp4");
    IPlayerProxy::Get()->Start();

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    //视频显示
    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    IPlayer::Get()->InitView(win);
}