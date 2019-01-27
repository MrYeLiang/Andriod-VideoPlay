//
// Created by 叶亮 on 2019/1/25.
//

#include <jni.h>
#include <string>

#include "FFDemux.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_MainActivity_decode(JNIEnv *env, jobject instance) {

    IDemux *de = new FFDemux();
    de->Open("");
}


