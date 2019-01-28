//
// Created by 叶亮 on 2019/1/27.
//

#ifndef VIDEOPLAY_XDATA_H
#define VIDEOPLAY_XDATA_H

struct XData {
    unsigned char *data = 0;
    int size = 0;
    void Drop();
};
#endif //VIDEOPLAY_XDATA_H
