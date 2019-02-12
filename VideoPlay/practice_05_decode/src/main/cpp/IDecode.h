//
// Created by 叶亮 on 2019/2/12.
//

#ifndef VIDEOPLAY_IDECODE_H
#define VIDEOPLAY_IDECODE_H

#include "IObserver.h"
#include "XParameter.h"

//解码接口，支持硬解码
class IDecode:public IObserver
{
public:
    //打开解码器
    virtual bool Open(XParameter para) = 0;
};
#endif //VIDEOPLAY_IDECODE_H
