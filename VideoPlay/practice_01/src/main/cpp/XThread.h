//
// Created by 叶亮 on 2018/12/2.
//

#ifndef VIDEOPLAY_XTHREAD_H
#define VIDEOPLAY_XTHREAD_H

//sleep 毫秒
void XSleep(int mis);

//c++ 11线程
class XThread {
public:
    //启动线程
    virtual bool Start();

    //通过控制isExit安全停止线程(不一定成功)
    virtual void Stop();

    virtual void Main() {};

protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};

#endif //VIDEOPLAY_XTHREAD_H
