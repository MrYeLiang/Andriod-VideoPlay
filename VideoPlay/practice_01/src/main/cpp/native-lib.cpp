
//
// Created by 叶亮 on 2018/12/1.
//
#include <jni.h>
#include <android/native_window_jni.h>
#include "IPlayerProxy.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_practice_01_videoplay_SurfaceView_initView(JNIEnv *env,
                                                    jobject instance, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(win);
}