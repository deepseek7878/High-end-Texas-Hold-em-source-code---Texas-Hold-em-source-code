#ifndef _USERSTATE_PROCESSOR_H_
#define _USERSTATE_PROCESSOR_H_

//
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <wbl/regex_util.h>
#include <wbl/pthread_util.h>
#include <util/tc_singleton.h>
#include "UserStateProto.h"

//
using namespace std;
using namespace tars;
using namespace wbl;

//在线用户状态信息
class Player : public TC_HandleBase
{
public:
    Player()
    {
        _uid = 0L;
        _cid = 0L;
        _router = "";
        _lastUpdateTime = 0L;
    }

    virtual ~Player()
    {

    }
    //
    const long getUid()
    {
        return _uid;
    }
    //
    void SetUid(const long uid)
    {
        _uid = uid;
    }
    //
    const long getCid()
    {
        return _cid;
    }
    //
    void setCid(const long cid)
    {
        _cid = cid;
    }
    //
    const std::string &getRouter()
    {
        return _router;
    }
    //
    void SetRouter(const std::string &addr)
    {
        _router = addr;
    }
    //
    long GetLastUpdateTime()
    {
        return _lastUpdateTime;
    }
    //
    void SetLastUpdateTime(const long time)
    {
        _lastUpdateTime = time;
    }
    //
private:
    //用户全局标识
    long _uid;
    //网关会话标识
    long _cid;
    //网关地址信息
    std::string _router;
    //上次更新信息时间
    long _lastUpdateTime;
};

typedef TC_AutoPtr<Player> PlayerPtr;

/**
 *请求处理类
 */
class UserStateProcessor
{
public:
    UserStateProcessor();
    ~UserStateProcessor();

public:
    //USER_STATE_ONLINE = 31,       //玩家在线状态，uid<==>online state
    //查询
    int selectUserStateOnline(long uid, userstate::UserOnlineState &onlineState);
    //增加
    int UpdateUserStateOnline(long uid, const string &gwAddr, const long gwCid);
    //删除
    int deleteUserStateOnline(long uid);

    //USER_STATE_GAME   = 32,        //玩家游戏在线状态，uid<==>game state
    //查询
    int selectUserStateGame(long uid, userstate::GameState &gameState);
    //增加
    int UpdateGameInfo(long uid, const string &gameAddr, const string &sRoomID);
    //删除
    int deleteGameInfo(long uid);
    //重置
    int resetGameInfo(long uid);

    //USER_STATE_ONLINE_STATISTICS = 33;   //玩家在线统计
    //查询
    int CountStatistics(userstate::OnlinePlayerListResp &resp, bool isExcludeRobot = false);
    //增加
    int UpdateStatistics(long uid);
    //删除
    int deleteStatistics();
    //移除
    int rmStatistics(long uid);
    //
    int getOnlineUsersNew(std::vector<long> &uids, int LimitNum);
    //获取在线用户标识
    int getOnlineUsers(std::map<long, long> &uids, bool isExcludeRobot = false);
    //更新在线用户信息
    int updateOnlineUser(const long uid, const long cid, const std::string &addr);
    //清除在线信息冗余
    int cleanOnlineUser(bool isExcludeRobot = false);

private:
    //在线用户列表
    std::map<long, long> m_mapOnline;
    //在线用户表锁
    wbl::ReadWriteLocker m_rwlock;
};

//singleton
typedef TC_Singleton<UserStateProcessor, CreateStatic, DefaultLifetime> UserStateSingleton;

#endif

