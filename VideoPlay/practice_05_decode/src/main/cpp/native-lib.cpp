//
// Created by 叶亮 on 2019/1/25.
//

#include <jni.h>
#include "FFDemux.h"
#include "Xlog.h"
#include "IObserver.h"
#include "XData.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

class TestObs:public IObserver
{
public:
    void Update(XData d)
    {
        //XLOGI("TestObs Update data size is %d",d.size);
    }
};

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_MainActivity_decode(JNIEnv *env, jobject instance) {

    /*IDemux *de = new FFDemux();
    de->Open("");*/

    //测试代码
    TestObs *obs = new TestObs();
    IDemux *de = new FFDemux();
    de->AddObs(obs);
    de ->Open("/storage/emulated/0/video.mp4");

    int tid = (int)syscall(SYS_gettid);
    XLOGI("主进程id: = %d",tid);

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *aDecode = new FFDecode();
    aDecode->Open(de->GetAPara());


    de->Start();
    aDecode->Start();
    vdecode->Start();


    /*XSleep(3000);
    de->Stop();*/

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);
    XEGL::Get()->Init(win);
    XShader shader;
    shader.Init();
}