//
// Created by 叶亮 on 2018/12/3.
//

#ifndef VIDEOPLAY_FFDEMUX_H
#define VIDEOPLAY_FFDEMUX_H

struct AVFormatContext;

class FFDemux:public IDemux{

public:
    virtual bool Open(const char *url);
    virtual void Close();

    //获取视频参数
    virtual XParameter GetVPara();

    //获取音频参数
    virtual XParameter GetAPara();

    //读取一帧数据 数据有调用者清理
    virtual XData Read();

    FFDemux();

private:
    AVFormatContext *ic = 0;
    std::mutex mutex;
    int audioStream  = 1;
    int videoStream = 0;
};


#endif //VIDEOPLAY_FFDEMUX_H
