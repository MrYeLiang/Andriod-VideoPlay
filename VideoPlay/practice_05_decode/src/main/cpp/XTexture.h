//
// Created by 叶亮 on 2019/2/13.
//

#ifndef VIDEOPLAY_XTEXTURE_H
#define VIDEOPLAY_XTEXTURE_H

class XTexture
{
public:
    static XTexture *Create();
    virtual bool Init(void *win) = 0;
    virtual void Draw(unsigned char *data[], int width, int heigth) = 0;
};
#endif //VIDEOPLAY_XTEXTURE_H
