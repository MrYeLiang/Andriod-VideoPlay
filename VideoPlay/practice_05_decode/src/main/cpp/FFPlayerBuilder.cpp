//
// Created by 叶亮 on 2019/3/4.
//
#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "FFResample.h"
#include "GLVideoView.h"
#include "SLAudioPlay.h"

IDemux *CreateDemux()
{
    IDemux *ffdemux = new FFDemux();
    return ffdemux;
};

IDecode *CreateDecode()
{
    IDecode *ffdecode = new FFDecode();
    return ffdecode;
};

IResample *CreateResample()
{
    IResample *ffresample = new FFResample();
    return ffresample;
};

IVideoView *CreateVideoView()
{
    IVideoView *glVideoView = new GLVideoView();
    return glVideoView;
};

IAudioPlay *CreateAudioPlay()
{
    IAudioPlay *slAudioPlay = new SLAudioPlay();
    return slAudioPlay;
};

IPlayer *CreatePlayer(unsigned char index = 0)
{
    return IPlayer::Get(index);
};

void FFPlayerBuilder::InitHard(void *vm)
{
    FFDecode::InitHard(vm);
}
