//
// Created by 叶亮 on 2018/12/6.
//
#include "IAudioPlay.h"

void IAudioPlay::Clear()
{
    framesMutext.lock();
    while(!frames.empty()){
        frames.front().Drop();
        frames.pop_front();
    }
    framesMutext.unlock();
}

XData IAudioPlay::GetData()
{
    XData d;
    while(!isExit)
    {
        framesMutext.lock();
        if(!frames.empty()){
            //有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutext.unlock();
            pts = d.pts;
            return d;
        }
        framesMutext.unlock();
        XSleep(1);
    }

    //未获取到数据
    return d;
}

void IAudioPlay::Update(XData data)
{
    //压入缓冲队列
    if(data.size<=0 || !data.data) return;
    while (!isExit){
        framesMutext.lock();
        if(frames.size()>maxFrame){
            framesMutext.unlock();
            XSleep(1);
            continue;
        }

        frames.push_back(data);
        framesMutext.unlock();
        break;
    }
}