//
// Created by 叶亮 on 2018/12/1.
//

#ifndef VIDEOPLAY_IPLAYERPROXY_H
#define VIDEOPLAY_IPLAYERPROXY_H


#include <mutex>

class IPlayerProxy : public IPlayerProxy {
public:
    static IPlayerProxy *Get() {
        static IPlayerProxy px;
        return &px;
    }

    void Init(void *vm = 0);

    virtual bool Open(const char *path);

    virtual bool Close();

    virtual bool Start();

    virtual void InitView(void *win);

protected:
    IPlayerProxy() {}

    IPlayerProxy *player = 0;
    std::mutex mux;
};

#endif //VIDEOPLAY_IPLAYERPROXY_H
