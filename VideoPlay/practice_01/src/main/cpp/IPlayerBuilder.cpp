//
// Created by 叶亮 on 2018/12/2.
//
#include "IPlayerBuilder.h"
#include "IDemux.h"
#include "IDecode.h"

IPlayer *IPlayerBuilder::BuilderPlayer(unsigned char index) {
    IPlayer *play = CreatePlayer(index);

    //解封装
    IDemux *de = CreateDemux();

    //视频解码
    IDecode *vdecode = CreateDecode();

    //音频解码
    IDecode *adecode = CreateDecode();

    //解码器观察解封装
    de->AddObs(vdecode);
    de->AddObs(adecode);

}