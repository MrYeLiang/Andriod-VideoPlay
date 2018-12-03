//
// Created by 叶亮 on 2018/12/3.
//

#ifndef VIDEOPLAY_FFDEMUX_H
#define VIDEOPLAY_FFDEMUX_H

#include "IDemux.h"
#include <mutex>

struct AVForMatContext;

class FFDemux: public IDemux{
public:

    //打开文件 或者流媒体
    virtual  bool Open(const char *url);
    virtual  void Close();

    //获取视频参数
    virtual XParameter GetVPara();

    //获取音频参数
    virtual XParameter GetAPara();

    //读取一帧数据 数据由调用者清理
    virtual XData Read();

    FFDemux();

private:
    AVForMatContext *ic = 0;
    std::mutex mux;
    int audioStream = 1;
    int videoStream = 0;
};
#endif //VIDEOPLAY_FFDEMUX_H
