//
// Created by 叶亮 on 2019/3/4.
//

#include "IPlayer.h"
#include "Xlog.h"
#include "IPlayer.h"

IPlayer *IPlayer::Get(unsigned char index)
{
    static IPlayer p[256];
    return &p[index];
}

bool IPlayer::Open(const char *path)
{
    //解封装
    if(!demux || !demux->Open(path)){
        XLOGE("demux->Open %s failed!", path);
        return false;
    }

    //解码 如果解封装之后是原始数据解码可能不需要
    if(!vdecode || !vdecode->Open(demux->GetVPara(),isHardDecode)){
        XLOGE("vdecode->Open %s failed!",path);
        //return false;
    }

    if(!vdecode || !adecode->Open(demux->GetAPara()))
    {
        XLOGE("adecode->Open %s failed!", path);
    }

    //重采样，有可能不需要  解码或者解封装后可能是直接能播放的数据
    if(outPara.sample_rate <= 0) outPara = demux->GetAPara();

    if(!resample || !resample->Open(demux->GetAPara(),outPara))
    {
        XLOGE("resample->Open %s failed!",path);
    }

    return true;
}

bool IPlayer::Start()
{
    if(!demux || !demux->Start())
    {
        XLOGE("demux->Start failed!");
        return false;
    }

    if(adecode)
    {
        adecode->Start();
    }

    if(audioPlay){
        audioPlay->StartPlay(outPara);
    }

    if(vdecode){
        vdecode->Start();
    }
    return true;
}

void IPlayer::InitView(void *win)
{
    if(videoView)
    {
        videoView->SetRender(win);
    }
}