#ifndef _PushServer_H_
#define _PUshServer_H_

#include <iostream>
#include <atomic>
#include "servant/Application.h"
#include "OuterFactoryImp.h"
#include "Functor.h"
#include "util/tc_timeout_queue.h"

//
using namespace tars;

/**
 * 推送服务
 **/
class PushServer : public Application
{
public:
    /**
     *
     **/
    virtual ~PushServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();

    /**
    * 初始化所有线程
    */
    void initialThread();

    /**
     * 结束所有线程
     */
    void destroyThread();

public:
    /*
     * 配置变更，重新加载配置
     */
    bool reloadSvrConfig(const string &command, const string &params, string &result);
    /*
     * 清除在线玩家状态
     * params : 指定在线玩家uid,如果为-1,则表示清除所有在线玩家
     *          example -> CleanOnlineUser -1 or CleanOnlineUser 123456
     */
    bool cleanOnlineUser(const string &command, const string &params, string &result);
    /*
     * 服务器维护
     * params : 分钟数
     *          example -> ServerUpdate 5
     */
    bool serverUpdate(const string &command, const string &params, string &result);

    /**
     * 零点在线状态重置
     */
    bool dailyReset(const string &command, const string &params, string &result);

    /**
     * 打印在线用户信息
     */
    bool printOnlineUsers(const string &command, const string &params, string &result);

    /**
    * 打印机器人信息
    */
    bool printOnlineRobots(const string &command, const string &params, string &result);

public:
    /**
    * 初始化外部接口对象
    **/
    int initOuterFactory();

    /**
    * 取外部接口对象
    **/
    OuterFactoryImpPtr getOuterFactoryPtr()
    {
        return _pOuter;
    }

private:
    //外部接口对象
    OuterFactoryImpPtr _pOuter;
    //定时处理对象
    Functor _functor;
    //线程池
    TC_ThreadPool _tpool;
    //锁，用于保护连接安全
    TC_ThreadMutex m_ThreadMutex;
};

////
extern PushServer g_app;

////////////////////////////////////////////
#endif
