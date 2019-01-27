//
// Created by 叶亮 on 2019/1/27.
//

#ifndef VIDEOPLAY_IDEMUX_H
#define VIDEOPLAY_IDEMUX_H

#include "XData.h"
//解封装接口
class IDemux {
public:
        //打开文件， 或者流媒体 rtmp http rtsp
    virtual bool Open(const char *url) = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData Read() = 0;
};
#endif //VIDEOPLAY_IDEMUX_H
