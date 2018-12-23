//
// Created by 叶亮 on 2018/12/23.
//

#ifndef VIDEOPLAY_XEGL_H
#define VIDEOPLAY_XEGL_H

class XEGL
{
public:
    virtual bool Init(void *win) = 0;
    virtual void Close() = 0;
    virtual void Draw() = 0;
    static XEGL *Get();

protected:
    XEGL(){}
};
#endif //VIDEOPLAY_XEGL_H
