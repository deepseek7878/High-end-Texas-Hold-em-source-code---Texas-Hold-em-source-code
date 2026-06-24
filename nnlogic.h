#pragma once

#include <random>
#include <algorithm>

#include "common/nndef.h"

using namespace nndef;
using namespace nncard;
using namespace nninvalid;

namespace nnlogic
{
    extern const short CONST_CARD_NUM;

    int nnrand(int max, int min = 0);
    void build(vecc_t &vSrcCards);

    template<typename T>
    void shuffle(std::vector<T> &vSrc)
    {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(vSrc.begin(), vSrc.end(), g);
    }

    void deal(vecc_t &vSrcCards, vecc_t &vDstCards, int iNum);

    void sort(vecc_t &vSrcCards);
    bool isminmaxboom2(map<card_t, int>& airplane_result);
    bool isevennum(vecc_t &vCards, map<card_t, int>& result);
    int isstraight(vecc_t &vCards, int num);
    int isairplan(std::vector<int> vCards, vecc_t& vAirPlane) ;
    int findmaxface(map<card_t, int>& result);

    bool findgtcardgroup(vecc_t &vHdCards, vecc_t &vLastCards, E_NN_TYPE checkCardType);
    bool findcardgroup(E_NN_TYPE cardType, vecc_t &vLastCards, map<card_t, int>& lastResult, card_t& maxLastAirPlane, map<card_t, int>& hdResult);

    int check(vecc_t &vOutCards, vecc_t &vHdCards, map<cid_t, vecc_t>& mLastDeision, E_NN_TYPE checkCardType, E_NN_TYPE& outCardType, int checkType = 0);
    int compare(vecc_t &vOutCards, vecc_t &vLastCards, E_NN_TYPE checkCardType, E_NN_TYPE& outCardType);
    E_NN_TYPE calcardtype(vecc_t &vCards, map<card_t, int>& result, E_NN_TYPE checkCardType, card_t& maxAirPlane = nil_card);
    E_NN_TYPE checkthreeandboom(vecc_t &vCards, map<card_t, int>& result, card_t& maxAirPlane = nil_card);
    
    void cardgroup(vecc_t &vCards, map<card_t, int>& result);
    void cardgroup(map<card_t, int>& result, map<int, vecc_t>& m_num_card);
    void cardgroup(map<card_t, int>& result, map<int, vecc_t>& m_num_card, int cardnum);
  
    void vecremove(vecc_t &vSrcCards1, vecc_t &vSrcCards2);
    void vecremove2(vecc_t &vSrcCards, card_t face);

    template<typename T>
    bool vecfind(std::vector<T> const &vecSrc, T t)
    {
        typename std::vector<T>::const_iterator it = std::find(vecSrc.begin(), vecSrc.end(), t);
        return it != vecSrc.end();
    }

    template<typename T>
    bool vecfind(std::vector<T> const &vecSrc1, std::vector<T> const &vecSrc2)
    {
        for(typename std::vector<T>::const_iterator it = vecSrc2.begin();  it != vecSrc2.end(); it++)
        {
            if(!vecfind<T>(vecSrc1, *it))
            {
                return false;
            }
        }

        return true;
    }

    template<typename T>
    bool vecfind(std::vector<std::vector<T> > const &vecSrc1, std::vector<T> const &vecSrc2)
    {
        for (typename std::vector<std::vector<T> >::const_iterator it = vecSrc1.begin(); it != vecSrc1.end(); it++)
        {
            if(vecfind<T>(*it, vecSrc2))
            {
                return true;
            }
        }

        return false;
    }
};