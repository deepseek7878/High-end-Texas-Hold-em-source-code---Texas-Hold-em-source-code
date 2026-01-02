#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include <sys/time.h>
#include "util/tc_thread.h"
#include "globe.h"
#include "OuterFactoryImp.h"

//
using namespace tars;

// 线程停止标记
extern volatile bool g_bStop;

/***
**
* 定时接口
**/
class Functor
{
public:
    typedef enum
    {
        eUpdateOnlineNumber = 0,  //更新在线人数
        eUpdateUserPlayState = 1, //零点更新状态
    } DoType;

public:
    Functor();
    virtual ~Functor();

public:
    //事件处理
    void operator()(int t);
    //终止处理
    void stop();

private:
    //更新在线人数
    void updateOnlineNumber();
    //更新玩家状态
    void updateUserPlayState();

private:
    //更新路由最近时间
    time_t iLastUpdateOnlineTime;
    //上次更新玩家状态时间
    time_t iLastUpdateStateTime;
};

#endif



