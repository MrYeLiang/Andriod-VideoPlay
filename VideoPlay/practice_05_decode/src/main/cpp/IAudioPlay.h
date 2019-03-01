//
// Created by 叶亮 on 2019/2/28.
//

#ifndef VIDEOPLAY_IAUDIOPLAY_H
#define VIDEOPLAY_IAUDIOPLAY_H

#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver
{
public:
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;
};
#endif //VIDEOPLAY_IAUDIOPLAY_H
