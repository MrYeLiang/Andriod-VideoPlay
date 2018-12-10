//
// Created by 叶亮 on 2018/12/4.
//

#ifndef VIDEOPLAY_FFDECOE_H
#define VIDEOPLAY_FFDECOE_H

#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode:public IDecode
{
public:
    static void InitHard(void *vm);

    virtual bool Open(XParameter para,bool isHard = false);

    virtual void Close();

    //future模型 发型数据到线程解码
    virtual bool SendPacket(XData pkt);

    //从线程中获取解码结果，再次调用会复用上次空间，线程不安全
    virtual XData RecvFrame();

protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
    std::mutex mux;

};
#endif //VIDEOPLAY_FFDECOE_H
