//
// Created by 叶亮 on 2018/12/22.
//

#include "GLVideoView.h"

void GLVideoView::SetRender(void *win)
{
    view = win;
}

void GLVideoView::Close()
{
    mux.lock();
    if(txt){
        txt ->Drop();
        txt = 0;
    }
}