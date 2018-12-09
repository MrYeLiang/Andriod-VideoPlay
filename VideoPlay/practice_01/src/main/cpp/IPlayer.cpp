//
// Created by 叶亮 on 2018/12/6.
//
#include "IPlayer.h"
#include "IAudioPlay.h"
#include "IDecode.h"
#include "IDemux.h"
#include "IVideoView.h"
#include "XLog.h"
#include "IResample.h"



IPlayer *IPlayer::Get(unsigned char index)
{
    static IPlayer p[256];
    return &p[index];
}

void IPlayer::Main()
{
    while(!isExit)
    {
        mux.lock();
        if(!audioPlay||!vdecode){
            mux.unlock();
            XSleep(2);
            continue;
        }

        //获取音频pts 告诉视频
        int apts = audioPlay->pts;
        vdecode->synPts = apts;
        mux.unlock();
        XSleep(2);
    }
}

void IPlayer::Close()
{
    mux.lock();
    //1 先关闭主体线程，再清理观察者
    //同步线程
    XThread::Stop();
    //解封装
    if(demux){
        demux->Stop();
    }
    //解码
    if(vdecode){
        vdecode->Stop();
    }
    if(adecode){
        adecode->Stop();
    }
    //2 清理缓冲队列
    if(vdecode){
        vdecode->Clear();
    }
    if(adecode){
        adecode->Clear();
    }
    if(audioPlay){
        audioPlay->Clear();
    }

    //清理资源
    if(audioPlay){
        audioPlay->Close();
    }
    if(videoView){
        videoView->Close();
    }

}

bool IPlayer::Open(const char *path)
{
    Close();
    mux.lock();
    //解封装
    if(!demux || !demux->Open(path)){
        mux.unlock();
        XLOGE("demux->Open %s failed!",path);
        return false;
    }

    //解码 解码可能不需要 如果解封之后就是原始数据
    if(!vdecode || !vdecode->Open(demux->GetVPara(),isHardDecode)){
        XLOGE("vdecode->Open %s failed!",path);
    }

    if(!adecode || !adecode->Open(demux->GetAPara())){
        XLOGE("adecode->Open %s failed!",path);
    }

    //重采样 有可能不需要 解码后或者解封后可能是直接能播放的数据
    outPara = demux->GetAPara();
    if(!resample || !resample->Open(demux->GetAPara(),outPara)){
        XLOGE("resample->Open %s failed!"path);
    }
    mux.unlock();
    return true;
}

bool IPlayer::Start()
{
    mux.lock();
    if(vdecode){
        vdecode->Start();
    }

    if(!demux || !demux->Start()){
        mux.unlock();
        XLOGE("demux->Start failed!");
        return false;
    }
    if(adecode){
        adecode->Start();
    }
    if(audioPlay){
        audioPlay->StartPlay(outPara);
    }
    XThread::Start();
    mux.unlock();
    return true;
}

void IPlayer::InitView(void *win)
{
    if(videoView){
        videoView->Close();
        videoView->SetRender(win);
    }
}