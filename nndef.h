#pragma once

#include<vector>

namespace nndef
{
    namespace nnuser
    {
        typedef short cid_t;
        typedef long guid_t;
    };

    namespace nncard
    {
        typedef short card_t;
        typedef std::vector<card_t> vecc_t;

        //花色类型 不同的牌值用个位标识
        enum E_NN_CARD
        {
            NN_CARD_DIAMOND = 0x0000, //方
            NN_CARD_CLUB    = 0x0010, //梅
            NN_CARD_HEART   = 0x0020, //红
            NN_CARD_SPADE   = 0x0030, //黑
            NN_CARD_KING    = 0x0040, //大小王
        };

        //获取花色
        card_t getNNType(card_t card);

        //获取计算牛值
        card_t getNNValue(card_t card);

        //获取数值
        card_t getNNNum(card_t card);
    };

    //牌型
    enum E_NN_TYPE
    {
        NN_TYPE_NN_NONE = -1,   
        NN_TYPE_NN_SINGLE,          //单张
        NN_TYPE_NN_ONEPAIRS,        //一对
        NN_TYPE_NN_STRAIGHT,        //顺子
        NN_TYPE_NN_MULTPAIRS,       //连对
        NN_TYPE_NN_THREE,           //三条
        NN_TYPE_NN_THREEANDONE,     //三带一
        NN_TYPE_NN_THREEANDTWO,     //三带二
        NN_TYPE_NN_BOOMANDONE,      //四带一
        NN_TYPE_NN_BOOMANDTWO,      //四带二
        NN_TYPE_NN_AIRPLANE,        //飞机
        NN_TYPE_NN_AIRPLANEANDONE,  //飞机带单张
        NN_TYPE_NN_AIRPLANEANDTWO,  //飞机带对子
        NN_TYPE_NN_BOOM,            //炸弹
        NN_TYPE_NN_KING,            //王炸
    };

    //下注类型
    enum E_NN_ACT
    {
        NN_ACT_UNKNOWN   = 0x0001,  //未知
        NN_ACT_FOLD     = 0x0010,   //弃牌
        NN_ACT_PASS     = 0x0020,   //过
        NN_ACT_FOLLOW   = 0x0040,   //跟注
        NN_ACT_RAISE    = 0x0080,   //加注
        NN_ACT_ALLIN    = 0x0100,   //全下
    };

    //牌型
    enum E_NN_GUESS
    {
        NN_GUESS_1A = 0x0001,
        NN_GUESS_1P,            //对子
        NN_GUESS_AA,            //对A
    };

    enum E_NN_STATE
    {
        NN_STATE_SEND_CARD     = 0x0001,
        NN_STATE_JIAODIZHU     = 0x0002,
        NN_STATE_JIABEI        = 0x0003,
        NN_STATE_DAPAI         = 0x0004,
        NN_STATE_GAME_END      = 0x0005,
    };

    enum E_NN_XTIME
    {
        NN_XTIME_GAME_BEGIN = 170,
        NN_XTIME_GAME_XTIME,
        NN_XTIME_KILL_ALL,
    };

    enum E_NN_USER_STATE
    {
        NN_USER_STATE_NORMAL = 1,
        NN_USER_STATE_WIN,
        NN_USER_STATE_LOSE,
    };

    namespace nninvalid
    {
        using namespace nnuser;
        using namespace nncard;

        extern guid_t       nil_uid;
        extern cid_t        nil_cid;
        extern card_t       nil_card;

        extern E_NN_ACT     nil_act;
        extern E_NN_TYPE    nil_nntype;
        extern E_NN_STATE   nil_nnstate;
        extern E_NN_GUESS   nil_guess;
    };
};

