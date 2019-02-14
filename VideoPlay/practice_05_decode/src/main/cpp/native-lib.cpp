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
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"

class TestObs:public IObserver
{
public:
    void Update(XData d)
    {
        //XLOGI("TestObs Update data size is %d",d.size);
    }
};
IVideoView *view = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_decode(JNIEnv *env, jobject instance) {

}


extern "C"
JNIEXPORT void JNICALL
Java_com_example_videoplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    //测试代码
    IDemux *demux = new FFDemux();
    demux ->Open("/storage/emulated/0/video.mp4");

    /*int tid = (int)syscall(SYS_gettid);
    XLOGI("主进程id: = %d",tid);*/

    //IDecode *vdecode = new FFDecode();
    //vdecode->Open(demux->GetVPara());

    IDecode *aDecode = new FFDecode();
    aDecode->Open(demux->GetAPara());



    view = new GLVideoView();
    //vdecode->AddObs(view);

    IResample *resample = new FFResample();
    resample->Open(demux->GetAPara());
    aDecode->AddObs(resample);

    demux->AddObs(aDecode);
    //demux->AddObs(vdecode);
    demux->Start();
    aDecode->Start();
    //vdecode->Start();

    ANativeWindow *win = ANativeWindow_fromSurface(env,surface);

    view->SetRender(win);
}