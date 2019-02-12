//
// Created by 叶亮 on 2019/2/12.
//

#ifndef VIDEOPLAY_FFDECODE_H
#define VIDEOPLAY_FFDECODE_H

#include "IDecode.h"

struct AVCodecContext;

class FFDecode:public IDecode
{
public:
    virtual bool Open(XParameter para);

protected:
    AVCodecContext *codec = 0;
};
#endif //VIDEOPLAY_FFDECODE_H
