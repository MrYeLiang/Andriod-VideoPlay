//
// Created by 叶亮 on 2019/2/12.
//
#include "GLVideoView.h"
#include "XTexture.h"
#include "XData.h"
#include "Xlog.h"

void GLVideoView::SetRender(void *win)
{
    view = win;
}

void GLVideoView::Render(XData data)
{
    if(!view){
        return;
    }
    if(!txt){
        txt = XTexture::Create();
        txt->Init(view);
    }

    txt->Draw(data.datas, data.width, data.height);
}