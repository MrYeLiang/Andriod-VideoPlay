//
// Created by 叶亮 on 2018/12/4.
//

#ifndef VIDEOPLAY_IRESAMPLE_H
#define VIDEOPLAY_IRESAMPLE_H

#include "IObserver.h"
#include "../../../../test_01/src/main/cpp/XParameter.h"

class IResample: public IObserver
{
public:
    virtual bool Open(XParameter in,XParameter out = XParameter()) = 0;
    virtual XData Resample(XData indata) = 0;
    virtual void Close() = 0;
    virtual void Update(XData data);
    int outChannels = 2;
    int outFormat =1;
};
#endif //VIDEOPLAY_IRESAMPLE_H
