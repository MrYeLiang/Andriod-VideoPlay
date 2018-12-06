//
// Created by 叶亮 on 2018/12/1.
//

#ifndef VIDEOPLAY_IPLAYERPROXY_H
#define VIDEOPLAY_IPLAYERPROXY_H


#include <mutex>
#include "IPlayer.h"

class IPlayerProxy : public IPlayer {
public:
    static IPlayerProxy *Get() {
        static IPlayerProxy px;
        return &px;
    }

    void Init(void *vm = 0);

    virtual bool Open(const char *path);

    virtual void Close();

    virtual bool Start();

    virtual void InitView(void *win);

protected:
    IPlayerProxy() {}

    IPlayer *player = 0;
    std::mutex mux;
};

#endif //VIDEOPLAY_IPLAYERPROXY_H
