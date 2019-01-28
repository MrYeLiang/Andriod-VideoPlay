//
// Created by 叶亮 on 2019/1/28.
//

#include "XThread.h"
#include "Xlog.h"

#include <thread>

using namespace std;
void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

//启动线程
void XThread::Start()
{
    isExit = false;
    XLOGI("线程函数进入");
    thread th(&XThread::ThreadMain, this);
    XLOGI("线程函数退出");
    isRuning = false;
}

void XThread::ThreadMain()
{
    isRuning = true;
    XLOGI("线程函数进入");
    Main();
    XLOGI("线程函数退出");
    isRuning = false;
}

void XThread::Stop()
{
    XLOGI("Stop 停止线程begin!");
    isExit = true;
    for(int i = 0; i <200; i++){
        if(!isRuning){
            XLOGI("Stop 停止线程成功！");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop 停止线程超时");
}
