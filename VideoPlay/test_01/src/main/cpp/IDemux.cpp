


//
// Created by Administrator on 2018-03-01.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main()
{
    while(!isExit)
    {

        XData d = Read();
        if(d.size > 0)
            Notify(d);
        //XLOGI("IDemux Read %d",d.size);
        //if(d.size<=0)break;
    }
}