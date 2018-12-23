//
// Created by 叶亮 on 2018/12/22.
//
#include "XTexture.h"
#include "XLog.h"
#include "XShader.h"
#include "XEGL"

class CXTexture:public XTexture
{
public:
    XShader sh;
    XTextureType  type;
    std::mutex mux;
    virtual void Drop()
    {
        mux.lock();
        XEGL
    }
};