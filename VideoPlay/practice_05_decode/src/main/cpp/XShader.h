//
// Created by 叶亮 on 2019/2/12.
//

#ifndef VIDEOPLAY_XSHADER_H
#define VIDEOPLAY_XSHADER_H
class XShader
{
public:
    virtual bool Init();

protected:
    unsigned  int vsh = 0;
    unsigned  int fsh = 0;
    unsigned  int program = 0;
};
#endif //VIDEOPLAY_XSHADER_H
