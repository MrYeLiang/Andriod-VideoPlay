//
// Created by 叶亮 on 2018/12/2.
//

#ifndef VIDEOPLAY_IPLAYER_H
#define VIDEOPLAY_IPLAYER_H

#include <mutex>
#include "XThread.h"
#include "XParameter.h"

class IDemux;

class IAudioPlay;

class IVideoView;

class IResample;

class IDecode;

class IPlayer : public XThread {
public:
    static IPlayer *Get(unsigned char index = 0);

    virtual bool Open(const char *path);

    virtual void Close();

    virtual bool Start();

    virtual void InitView(void *win);

    bool isHardDecode = true;

    //音频输出参数硬编码
    XParameter outPara;

    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    void Main();

    std::mutex mux;

    IPlayer() {};
};

#endif //VIDEOPLAY_IPLAYER_H
