#ifndef _OUTER_FACTORY_IMP_H_
#define _OUTER_FACTORY_IMP_H_

#include <string>
#include <map>

//
#include "servant/Application.h"
#include "globe.h"
#include "OuterFactory.h"

//wbl
#include <wbl/regex_util.h>

//配置服务
#include "ConfigServant.h"
#include "DBAgentServant.h"
#include "HallServant.h"
#include "LoginServant.h"

//
using namespace config;
using namespace dataproxy;
using namespace dbagent;
using namespace hall;
using namespace login;
//
#define ONE_DAY_TIME (24*60*60)
#define ZONE_TIME_OFFSET (8*60*60)

//
class OuterFactoryImp;
typedef TC_AutoPtr<OuterFactoryImp> OuterFactoryImpPtr;

/**
 * 外部工具接口对象工厂
 */
class OuterFactoryImp : public OuterFactory
{
private:
    /**
     *
    */
    OuterFactoryImp();

    /**
     *
    */
    ~OuterFactoryImp();

    /**
     *
     */
    friend class PushServantImp;

    /**
     *
     */
    friend class PushServer;

public:
    //框架中用到的outer接口(不能修改):
    const OuterProxyFactoryPtr &getProxyFactory() const
    {
        return _pProxyFactory;
    }

    //
    tars::TC_Config &getConfig() const
    {
        return *_pFileConf;
    }

public:
    //读取所有配置
    void load();
    //代理配置
    void readPrxConfig();
    //打印代理配置
    void printPrxConfig();
    //加载在线人数配置
    void readOnlineNumber();
    //打印在线人数配置
    void printOnlineNumber();
    //设置在线人数
    void setOnline();
    //取在线人数
    int getOnline();
    //加载在线人数时间间隔
    void readOnlineInterval();
    //打印在线人数时间间隔
    void printOnlineInterval();
    //取在线人数时间间隔
    int getOnlineInterval();
    //清除在线玩家状态
    int cleanOnlineStatus(long user_id = -1);

public:
    //范围随机数
    int nnrand(int max, int min = 0);

private:
    //
    void createAllObject();
    //
    void deleteAllObject();

public:
    //游戏配置服务代理
    const ConfigServantPrx getConfigServantPrx();
    //数据库代理服务代理
    const DBAgentServantPrx getDBAgentServantPrx(const long uid);
    //数据库代理服务代理
    const DBAgentServantPrx getDBAgentServantPrx(const string key);
    //广场信息服务代理
    const HallServantPrx getHallServantPrx(const long uid);
    //广场信息服务代理
    const HallServantPrx getHallServantPrx(const string key);
    //网关推送服务名称
    const std::string getRouterPushObj();
    //游戏登录服务代理
    const LoginServantPrx getLoginServantPrx(const long uid);
    //游戏登录服务代理
    const LoginServantPrx getLoginServantPrx(const string key);

public:
    //格式化时间
    string GetTimeFormat();
    //获得时间秒数
    int GetTimeTick(const string &str);
    //获取自定义年月日
    int GetCustomDateFormat(int time);
    //获取当天零点秒数
    int GetZeroTimeTick(int time);

public:
    //加载通用配置
    void readGeneralConfigResp();
    //
    void printGeneralConfigResp();
    //
    const config::ListGeneralConfigResp &getGeneralConfigResp();
    //
    bool readRobotListResp();
    //
    void printRobotListResp();
    //
    const std::vector<tars::Int64> &getRobotList();

public:
    //异步广播所有网关
    void asyncBroadcastRouterServer(const long uid, const long cid, const string &addr, const int state, const string &data);
    //异步更新用户状态时间
    void asyncUserStateNotify(const long uid);

private:
    //拆分字符串成整形
    int splitInt(string szSrc, vector<int> &vecInt);

private:
    //读写锁，防止脏读
    wbl::ReadWriteLocker m_rwlock;

private:
    //框架用到的共享对象(不能修改):
    tars::TC_Config *_pFileConf;
    OuterProxyFactoryPtr _pProxyFactory;

private:
    //游戏配置服务
    std::string _ConfigServantObj;
    ConfigServantPrx _ConfigServerPrx;

    //数据库代理服务
    std::string _DBAgentServantObj;
    DBAgentServantPrx _DBAgentServerPrx;

    //HallServer的对象名称
    string _sHallServantObj;
    HallServantPrx _hallServerPrx;

    //RouterPushObj对象名称
    string _sRouterPushObj;

    //LoginServer的对象名称
    string _sLoginServantObj;
    LoginServantPrx _loginServerPrx;

private:
    //在线人数配置
    std::vector<int> m_onlineNumberRandom;
    //在线人数
    int online;
    //更新在线人数时间间隔
    int updateOnlineInterval;
    //通用配置
    config::ListGeneralConfigResp listGeneralConfigResp;
    //机器人列表
    std::vector<tars::Int64> robotList;
    //机器人表锁
    wbl::ReadWriteLocker robotLock;
};

////////////////////////////////////////////////////////////////////////////////
#endif


