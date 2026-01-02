#ifndef _PushServantImp_H_
#define _PushServantImp_H_

#include "servant/Application.h"
#include "PushServant.h"
#include "XGameComm.pb.h"
#include "CommonCode.pb.h"
#include "CommonStruct.pb.h"
#include "RedDot.pb.h"
#include "UserState.pb.h"

//
using namespace push;
using namespace userstate;

/**
 *推送服务逻辑处理接口
 *
 */
class PushServantImp : public push::PushServant
{
public:
    /**
     *
     */
    virtual ~PushServantImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

public:
    //http请求处理接口
    virtual tars::Int32 doRequest(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo,
                                  vector<tars::Char> &rspBuf, tars::TarsCurrentPtr current);
    //TCP请求处理接口
    virtual tars::Int32 onRequest(tars::Int64 lUin, const std::string &sMsgPack, const std::string &sCurServrantAddr,
                                  const JFGame::TClientParam &stClientParam, const JFGame::UserBaseInfoExt &stUserBaseInfo, tars::TarsCurrentPtr current);
public:
    //推送消息
    virtual tars::Int32 pushMsg(const push::PushMsgReq &req, tars::TarsCurrentPtr current);
    //推送广播
    virtual tars::Int32 pushBroadcast(const push::RewardNotify &notify, tars::TarsCurrentPtr current);
public:
    //报告在线状态
    virtual tars::Int32 reportOnlineState(const userstate::ReportOnlineStateReq &req, userstate::ReportOnlineStateResp &resp, tars::TarsCurrentPtr current);
    //报告游戏状态
    virtual tars::Int32 reportGameState(const userstate::ReportGameStateReq &req, userstate::ReportGameStateResp &resp, tars::TarsCurrentPtr current);
    //在线状态
    virtual tars::Int32 onlineState(const userstate::OnlineStateReq &req, userstate::OnlineStateResp &resp, tars::TarsCurrentPtr current);
    //批量获取在线状态
    virtual tars::Int32 batchOnlineState(const userstate::BatchOnlineStateReq &req, userstate::BatchOnlineStateResp &resp, tars::TarsCurrentPtr current);
    //获取游戏状态
    virtual tars::Int32 gameState(const userstate::GameStateReq &req, userstate::GameStateResp &resp, tars::TarsCurrentPtr current);
    //批量获取游戏状态
    virtual tars::Int32 batchGameState(const userstate::BatchGameStateReq &req, userstate::BatchGameStateResp &resp, tars::TarsCurrentPtr current);
    //上报房间玩家集合
    virtual tars::Int32 reportRoomUsers(const std::string &roomId, const std::string &uids, const std::string &blindUids_5, const std::string &blindUids_9, const std::string &robotWin_5, const std::string &robotWin_9, tars::TarsCurrentPtr current);
    //补偿玩家金币
    virtual tars::Int32 returnCompensateGold(const std::string &roomId, tars::TarsCurrentPtr current);
    //在线玩家列表
    virtual tars::Int32 onlinePlayerList(userstate::OnlinePlayerListResp &resp, tars::TarsCurrentPtr current);
    //在线玩家列表
    virtual tars::Int32 getlinePlayerList(int limitNum, userstate::OnlinePlayerListResp &resp, tars::TarsCurrentPtr current);
    //上报房间桌子信息
    virtual tars::Int32 reportRoomTableInfo(const push::RoomTableInfo &data, tars::TarsCurrentPtr current);
    //服务器维护通知
    virtual tars::Int32 serverUpdateNotifyAll(const int time, tars::TarsCurrentPtr current);
    //在线信息获取
    virtual tars::Int32 onlineInfoUserList(const int type, int &userCount, tars::TarsCurrentPtr current);
    //网关在线信息上报
    virtual tars::Int32 onlineUserReport(const push::OnlineUserReportReq &req, push::OnlineUserReportResp &resp, tars::TarsCurrentPtr current);

public:
    //获取游戏状态
    int onGetGameState(const XGameComm::TPackage &pkg, const UserStateProto::GetGameStateReq &gameStateReq, const std::string &sCurServrantAddr);
    //批量取在线状态
    int onBatchOnlineState(const XGameComm::TPackage &pkg, const UserStateProto::BatchOnlineStateReq &batchOnlineStateReq, const std::string &sCurServrantAddr);
    //批量取游戏状态
    int onBatchGameState(const XGameComm::TPackage &pkg, const UserStateProto::BatchGameStateReq &batchGameStateReq, const std::string &sCurServrantAddr);
    //获取在线数量
    int onCountStatistics(const XGameComm::TPackage &pkg, const std::string &sCurServrantAddr);
    //获取用户补偿金币
    long getUserCompensateGold(long uid);
    //更新用户当天累计玩牌时间(秒)
    int updateUserCurIngameTime(tars::Int64 uid, tars::TarsCurrentPtr current);
    //检查用户是否在新手期
    int checkUserInNoviceDays(tars::Int64 uid, const int &subType, tars::TarsCurrentPtr current);
    //通知所有在线玩家
    int serverUpdateNotify(int minutes);
    //格式化参数
    long formatAccumulate(const std::string param_1, std::string param_2, std::string param_3);

public:
    //时钟周期回调
    tars::Int32 doCustomMessage(bool bExpectIdle = false);

private:
    //发送消息到客户端
    template<typename T>
    int toClientPb(const XGameComm::TPackage &tPackage, const std::string &sCurServrantAddr, XGameProto::ActionName actionName, const T &t);
    //发送消息到客户端
    template<typename T>
    int toClientPb2(const XGameComm::TPackage &tPkg, const long cid, const int state, const string &addr, XGameProto::ActionName action, const T &t);
    //发送消息到客户端
    template<typename T>
    int toClientPb(const XGameComm::TPackage &tPackage, const std::string &sCurServrantAddr, XGameProto::ActionName actionName, int serviceType, const T &t);

private:

};
/////////////////////////////////////////////////////
#endif
