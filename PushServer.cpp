#include "PushServer.h"
#include "PushServantImp.h"
#include "UserStateProcessor.h"

//
using namespace std;

/////
PushServer g_app;

////
extern std::atomic<bool> g_PushUpdateNotify;
extern long g_RemainingTime;

/////////////////////////////////////////////////////////////////
void
PushServer::initialize()
{
    //注册服务接口
    addServant<PushServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".PushServantObj");

    //初始化外部接口对象
    initOuterFactory();

    //初始化所有线程
    initialThread();

    //注册动态加载命令
    TARS_ADD_ADMIN_CMD_NORMAL("reload", PushServer::reloadSvrConfig);

    //清除在线玩家状态
    TARS_ADD_ADMIN_CMD_NORMAL("CleanOnlineUser", PushServer::cleanOnlineUser);

    //服务器维护
    TARS_ADD_ADMIN_CMD_NORMAL("ServerUpdate", PushServer::serverUpdate);

    //零点在线重置
    TARS_ADD_ADMIN_CMD_NORMAL("DailyReset", PushServer::dailyReset);

    //打印在线玩家
    TARS_ADD_ADMIN_CMD_NORMAL("PrintOnline", PushServer::printOnlineUsers);

    //打印在线机器人
    TARS_ADD_ADMIN_CMD_NORMAL("PrintRobots", PushServer::printOnlineRobots);
}

/////////////////////////////////////////////////////////////////
void PushServer::destroyApp()
{
    //结束所有线程
    //
    //
    destroyThread();
}

/*
* 配置变更，重新加载配置
*/
bool PushServer::reloadSvrConfig(const string &command, const string &params, string &result)
{
    try
    {
        getOuterFactoryPtr()->load();

        result = "reload server config success.";
        LOG_ERROR << "reloadSvrConfig: " << result << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = "catch unknown exception.";
    }

    result += "\n fail, please check it.";
    LOG_ERROR << "reloadSvrConfig: " << result << endl;
    return true;
}

/*
* 清除在线玩家状态
* params : 指定在线玩家uid,如果为-1,则表示清除所有在线玩家
*          example -> CleanOnlineUser -1 or CleanOnlineUser 123456
*/
bool PushServer::cleanOnlineUser(const string &command, const string &params, string &result)
{
    try
    {
        LOG_ERROR << "Enter clean online user, command : " << command << ", params : " << params << endl;

        int iRet = 0;
        if (params == "-1")
        {
            //所有在线玩家
            iRet = getOuterFactoryPtr()->cleanOnlineStatus();
        }
        else
        {
            long lUserId = S2L(params);
            if (lUserId < 0)
            {
                result = string("clean online user failed, error params : ") + params;
                LOG_ERROR << "clean online user falied, result : " << result << endl;
                return false;
            }

            //指定在线玩家
            iRet = getOuterFactoryPtr()->cleanOnlineStatus(lUserId);
        }

        if (iRet != 0)
        {
            result = string("clean online user cleanOnlineStatus falied, iRet : ") + I2S(iRet);
            LOG_ERROR << "clean online user falied, result : " << result << endl;
            return false;
        }

        LOG_ERROR << "clean online user cleanOnlineStatus finished." << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = string("catch unknown exception.");
    }

    result += string("\n fail, please check it.");
    LOG_DEBUG << "clean online user finished, result : " << result << endl;
    return true;
}

/*
* 服务器维护
* params : 分钟数
*          example -> ServerUpdate 5
*/
bool PushServer::serverUpdate(const string &command, const string &params, string &result)
{
    try
    {
        LOG_ERROR << "Enter server update, command : " << command << ", params : " << params << endl;

        int iMinutes = S2I(params);
        if (iMinutes <= 0)
        {
            result = string("server update failed, error params : ") + params;
            LOG_ERROR << "server update falied, result : " << result << endl;
            return false;
        }

        //通知所有在线玩家
        g_RemainingTime = iMinutes;
        g_PushUpdateNotify = true;
        LOG_ERROR << "server update pushServantImp.serverUpdateNotify finished." << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = string("catch unknown exception.");
    }

    result += string("\n fail, please check it.");
    LOG_ERROR << "server update finished, result : " << result << endl;
    return true;
}
/**
 * 零点在线状态重置
 */
bool PushServer::dailyReset(const string &command, const string &params, string &result)
{
    try
    {
        auto robots = g_app.getOuterFactoryPtr()->getRobotList();
        if (robots.empty())
        {
            g_app.getOuterFactoryPtr()->readRobotListResp();
            robots = g_app.getOuterFactoryPtr()->getRobotList();
            LOG_ERROR << "Load online robot list, robotNum: " << robots.size() << endl;
        }

        std::map<long, long> uids;
        UserStateSingleton::getInstance()->getOnlineUsers(uids, true);
        LOG_ERROR << "Update online player status, iOnlineNum: " << uids.size() << endl;

        for (auto iter = uids.begin(); iter != uids.end(); iter++)
        {
            long uid = (*iter).first;
            g_app.getOuterFactoryPtr()->asyncUserStateNotify(uid);
            LOG_ERROR << "Update player status, uid: " << uid << endl;
        }

        result = string("success");
        LOG_ERROR << "daily reset finished." << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = string("catch unknown exception.");
    }

    result += string("\n fail, please check it.");
    LOG_ERROR << "daily reset finished, result : " << result << endl;
    return true;
}

/**
 * 打印在线用户信息
 */
bool PushServer::printOnlineUsers(const string &command, const string &params, string &result)
{
    try
    {
        std::map<long, long> uids;
        UserStateSingleton::getInstance()->getOnlineUsers(uids, true);
        LOG_ERROR << "----------@Print onlineinfo list, playerNum: " << uids.size() << endl;

        for (auto iter = uids.begin(); iter != uids.end(); iter++)
        {
            long uid = (*iter).first;
            long lastUpdateTime = (*iter).second;
            LOG_ERROR << "@Print onlineinfo, uid: " << uid << ",lastUpdateTime: " << lastUpdateTime << endl;
        }

        result = string("success");
        LOG_ERROR << "----------@Print onlineinfo finished." << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = string("catch unknown exception.");
    }

    result += string("\n fail, please check it.");
    LOG_ERROR << "print online finished, result : " << result << endl;
    return true;
}

/**
 * 打印在线机器人信息
 */
bool PushServer::printOnlineRobots(const string &command, const string &params, string &result)
{
    try
    {
        LOG_ERROR << "----------@Print robot list begin" << endl;
        g_app.getOuterFactoryPtr()->printRobotListResp();
        result = string("success");
        LOG_ERROR << "----------@Print robot finished." << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = string("catch unknown exception.");
    }

    result += string("\n fail, please check it.");
    LOG_ERROR << "print robot finished, result : " << result << endl;
    return true;
}
/**
* 初始化外部接口对象
**/
int PushServer::initOuterFactory()
{
    _pOuter = new OuterFactoryImp();
    return 0;
}

//初始化所有线程
void PushServer::initialThread()
{
    //定时启动线程
    _tpool.init(1);
    _tpool.start();

    std::function<void(int)> cmd(_functor);
    //更新在线人数
    // _tpool.exec(cmd, Functor::eUpdateOnlineNumber);
    //更新玩家状态
    _tpool.exec(cmd, Functor::eUpdateUserPlayState);
}

//结束所有线程
void PushServer::destroyThread()
{
    _functor.stop();

    LOG_DEBUG << "wait for all done ... " << endl;

    // 先等待一秒
    bool b = _tpool.waitForAllDone(1000);
    LOG_DEBUG <<  "wait for all done ... " << b << ":" << _tpool.getJobNum() << endl;

    if (!b)
    {
        // 没停止则再永久等待
        LOG_DEBUG << "wait for all done again, but forever..." << endl;
        b = _tpool.waitForAllDone(-1);
        LOG_DEBUG <<  "wait for all done again..." << b << ":" << _tpool.getJobNum() << endl;
    }

    //停止线程
    _tpool.stop();
}


/////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception &e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }

    return -1;
}
/////////////////////////////////////////////////////////////////
