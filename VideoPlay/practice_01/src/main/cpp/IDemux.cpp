//
// Created by 叶亮 on 2018/12/6.
//
#include "IDemux.h"

void IDemux::Main()
{
    while (!isExit)
    {
        XData d = Read();
        if(d.size > 0){
            Notify(d);
        }
    }
}