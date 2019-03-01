//
// Created by 叶亮 on 2019/2/28.
//

#ifndef VIDEOPLAY_IAUDIOPLAY_H
#define VIDEOPLAY_IAUDIOPLAY_H

#include "IObserver.h"
#include "XParameter.h"
#include <list>

class IAudioPlay: public IObserver
{
public:

    //缓冲满后阻塞
    virtual void Update(XData data);
    virtual bool StartPlay(XParameter out) = 0;

    //最大缓冲
    int maxFrame = 100;
protected:
    std::list <XData> frames;
    std::mutex framesMutex;
};
#endif //VIDEOPLAY_IAUDIOPLAY_H
