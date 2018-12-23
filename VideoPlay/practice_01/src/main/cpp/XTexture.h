//
// Created by 叶亮 on 2018/12/22.
//

#ifndef VIDEOPLAY_XTEXTURE_H
#define VIDEOPLAY_XTEXTURE_H

enum XTextureType
{
    XTEXTURE_YUV420P = 9,
    XTEXTURE_NV12 = 25,
    XTEXTURE_NV21 = 26
};

class XTexture
{
public:
    static XTexture *Create();
    virtual bool Init(void *win,XTextureType type = XTEXTURE_YUV420P) = 0;
    virtual void Draw(unsigned char *data[],int width, int height) = 0;
    virtual void Drop() = 0;
    virtual ~XTexture(){};

protected:
    XTexture(){};
};
#endif //VIDEOPLAY_XTEXTURE_H
