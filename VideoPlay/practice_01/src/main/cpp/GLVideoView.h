//
// Created by 叶亮 on 2018/12/4.
//

#ifndef VIDEOPLAY_GLVIDEOVIEW_H
#define VIDEOPLAY_GLVIDEOVIEW_H

#include "IVideoView.h"

class XTexture;

class GLVideoView:public IVideoView
{
public:
    virtual void SetRender(void *win);
    virtual void Render(XData data);
    virtual void Close();

protected:
    void *view = 0;
    XTexture *txt = 0;
    std::mutex mux;
};


#endif //VIDEOPLAY_GLVIDEOVIEW_H
