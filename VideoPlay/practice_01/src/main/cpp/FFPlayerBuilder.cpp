//
// Created by 叶亮 on 2018/12/3.
//

#include "IDemux.h"
#include "FFPlayerBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "IResample.h"
#include "FFResample.h"
#include "GLVideoView.h"

IDemux *FFPlayerBuilder::CreateDemux()
{
    IDemux *ff = new FFDemux();
    return ff;
}

IDecode *FFPlayerBuilder::CreateDecode()
{
    IDecode *ff = new FFDecode();
    return ff;
}

IResample *FFPlayerBuilder::CreateResample()
{
    IResample *ff = new FFResample();
    return ff;
}

IVideoView *FFPlayerBuilder::CreateVideoView()
{
    IVideoView *ff = new GLVideoView();
    return ff;
}

IAudioPlay *FFPlayerBuilder::CreateAudioPlay()
{
    IAudioPlay *ff = new SL
}

