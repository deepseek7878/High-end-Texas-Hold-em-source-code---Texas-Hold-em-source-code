#include "Functor.h"
#include "LogComm.h"
#include "PushServer.h"
#include "UserStateProcessor.h"
#include "util/tc_common.h"

//线程停止标记
volatile bool g_bStop = false;
//事件检查调整
#define SLEEP_INTERVAL 60
//一天秒数
#define ONE_DAY_SEC 86400

//获取当天000秒数
time_t GetTodayZeroTime(const long time, const int offset)
{
    time_t t = time_t(time);
    struct tm pTm;
    localtime_r(&t, &pTm);
    pTm.tm_hour = 0;
    pTm.tm_min = 0;
    pTm.tm_sec = 0;
    return mktime(&pTm) + offset;
}

Functor::Functor() : iLastUpdateOnlineTime(0), iLastUpdateStateTime(0)
{

}

Functor::~Functor()
{

}

//事件处理
void Functor::operator()(int t)
{
    if (t == eUpdateOnlineNumber)
    {
        updateOnlineNumber();
    }
    else if (t == eUpdateUserPlayState)
    {
        updateUserPlayState();
    }
}

//
void Functor::stop()
{
    g_bStop = true;
}

//更新在线人数
void Functor::updateOnlineNumber()
{
    __TRY__

    while (!g_bStop)
    {
        int interval = g_app.getOuterFactoryPtr()->getOnlineInterval();
        if (TNOW - iLastUpdateOnlineTime >= interval)
        {
            iLastUpdateOnlineTime = TNOW;
            g_app.getOuterFactoryPtr()->setOnline();
            int iOnlineNum = g_app.getOuterFactoryPtr()->getOnline();
            LOG_INFO << "Update the number of online players, iOnlineNum: " << iOnlineNum << endl;
        }

        TC_Common::sleep(SLEEP_INTERVAL);
    }

    __CATCH__
}

//更新玩家状态
void Functor::updateUserPlayState()
{
    __TRY__

    if (iLastUpdateStateTime == 0)
    {
        iLastUpdateStateTime = GetTodayZeroTime(TNOW, ONE_DAY_SEC);
    }

    while (!g_bStop)
    {
        LOG_DEBUG << "------------------->LastUpdateTime:" << iLastUpdateStateTime  << ", NowTime: " << TNOW << endl;

        //零点重置
        if (TNOW >= iLastUpdateStateTime)
        {
            iLastUpdateStateTime = GetTodayZeroTime(TNOW, ONE_DAY_SEC);

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
        }

        //冗余信息清除
        UserStateSingleton::getInstance()->cleanOnlineUser(true);

        TC_Common::sleep(SLEEP_INTERVAL);
    }

    __CATCH__
}

