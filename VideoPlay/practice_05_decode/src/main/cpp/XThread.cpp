//
// Created by 叶亮 on 2019/1/28.
//

#include "XThread.h"
#include "Xlog.h"
#include <thread>
#include <sys/syscall.h>
#include <unistd.h>

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
    thread th(&XThread::ThreadMain, this);
    th.detach();
}

void XThread::ThreadMain()
{
    isRuning = true;

    int tid = (int)syscall(SYS_gettid);

    Main();
    isRuning = false;
}

void XThread::Stop()
{
    isExit = true;
    for(int i = 0; i <200; i++){
        if(!isRuning){
            return;
        }
        XSleep(1);
    }
}
