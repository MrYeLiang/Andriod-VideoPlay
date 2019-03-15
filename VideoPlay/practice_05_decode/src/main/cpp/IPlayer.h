//
// Created by 叶亮 on 2019/3/4.
//

#ifndef VIDEOPLAY_IPLAYER_H
#define VIDEOPLAY_IPLAYER_H


#include "XThread.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IVideoView.h"
#include "IAudioPlay.h"

class IPlayer : public XThread{
public:
    static IPlayer *Get(unsigned char index = 0);
    virtual bool Open(const char *path);
    virtual bool Start();
    virtual void InitView(void *win);
    virtual void Close();

    //是否视频硬解码
    bool isHardDecode = true;

    //音频输出参数配置
    XParameter outPara;

    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    //用作音视频同步
    void Main();

    IPlayer(){};
    std::mutex mux;
};


#endif //VIDEOPLAY_IPLAYER_H
