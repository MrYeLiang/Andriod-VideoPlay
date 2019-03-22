//
// Created by 叶亮 on 2019/1/25.
//

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "FFPlayerBuilder.h"
#include "IPlayerProxy.h"


extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm, void *res) {
    FFPlayerBuilder::InitHard(vm);

    IPlayerProxy::Get()->Init(vm);

    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {
    //视频显示
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(win);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_PlayListActivity_OpenUrl(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, 0);

    IPlayerProxy::Get()->Open(url);
    IPlayerProxy::Get()->Start();

    env->ReleaseStringUTFChars(url_, url);
}