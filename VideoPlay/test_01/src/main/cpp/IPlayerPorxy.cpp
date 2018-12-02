


//
// Created by Administrator on 2018-03-07.
//

#include "IPlayerPorxy.h"
#include "FFPlayerBuilder.h"

void IPlayerPorxy::Close() {
    mux.lock();
    if (player)
        player->Close();
    mux.unlock();
}

void IPlayerPorxy::Init(void *vm) {
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player)
        player = FFPlayerBuilder::Get()->BuilderPlayer();

    mux.unlock();
}

bool IPlayerPorxy::Open(const char *path) {
    bool re = false;
    mux.lock();
    if (player)
        re = player->Open(path);
    mux.unlock();
    return re;
}

bool IPlayerPorxy::Start() {
    bool re = false;
    mux.lock();
    if (player)
        re = player->Start();
    mux.unlock();
    return re;
}

void IPlayerPorxy::InitView(void *win) {
    mux.lock();
    if (player)
        player->InitView(win);
    mux.unlock();
}