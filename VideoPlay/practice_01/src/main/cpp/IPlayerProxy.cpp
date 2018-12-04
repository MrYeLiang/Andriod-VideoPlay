//
// Created by 叶亮 on 2018/12/1.
//
#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"


void IPlayerProxy::Init(void *vm) {
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player) {
        //player = FFPlayerBuilder::Get()->BuilderPlayer();
    }
}

void IPlayerProxy::InitView(void *win) {
    mux.lock();
    if (player) {
        player->Init(win);
        mux.unlock();
    }
}
