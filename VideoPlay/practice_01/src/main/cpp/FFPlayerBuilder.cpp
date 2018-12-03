//
// Created by 叶亮 on 2018/12/3.
//

#include "IDemux.h"
#include "FFPlayerBuilder.h"

IDemux *FFPlayerBuilder::CreateDemux()
{
    IDemux *ff = new FFDemux();
}

