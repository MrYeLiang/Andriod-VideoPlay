//
// Created by 叶亮 on 2019/1/27.
//

#include "FFDemux.h"
#include "Xlog.h"

//打开文件 或者流媒体 rtmp http rtsp
bool FFDemux::Open(const char *url)
{
    XLOGI("Open file %s begin", url);
    return true;
}

//读取一帧数据，数据由调用者清理
XData FFDemux::Read()
{
    XData d;
    return d;
}