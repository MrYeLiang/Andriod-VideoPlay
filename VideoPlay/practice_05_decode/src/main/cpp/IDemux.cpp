//
// Created by 叶亮 on 2019/1/27.
//

#include "IDemux.h"
#include "XData.h"

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