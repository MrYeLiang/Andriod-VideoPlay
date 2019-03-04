//
// Created by 叶亮 on 2019/3/4.
//

#include "IPlayer.h"
#include "Xlog.h"

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

    return true;
}

bool IPlayer::Start()
{
    return true;
}
