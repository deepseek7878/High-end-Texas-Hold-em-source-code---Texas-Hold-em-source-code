/***************************************************************************************
#  Copyright (c) 2019
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:常用的一些宏定义, 短小的模板方法
#***************************************************************************************/

#ifndef __COMMON_MACROS_H__
#define __COMMON_MACROS_H__

#define __USE_IN_LIB__

#include "tup/Tars.h"
#include "utils/tarslog.h"
#include <google/protobuf/text_format.h>

#define To_uint(x)  TC_Common::strto<unsigned>(x)
#define To_int(x)   TC_Common::strto<int>(x)
#define To_bool(x)  TC_Common::strto<bool>(x)
#define BIN2S(s)    TC_Common::bin2str(s)
#define S2BIN(s)    TC_Common::str2bin(s)

#define VECTOR_LOG(log, vec, msg...)  \
do { \
    ostringstream os; \
    os << msg; \
    if(!vec.empty()) \
    { \
        os << ", " << vec.size() << "<" ;\
        for (const auto &v : vec)  \
        { \
            os << v << ", " ;\
        } \
        os << ">"; \
    } \
    os << endl; \
    log(os.str());\
} while(0)

////////////////////////////////////////////////////
//关闭拷贝构造
#define DISALLOW_COPY_AND_ASSIGN(c) \
    private: \
        c(const c &); \
        c & operator=(const c &);

////////////////////////////////////////////////////

//pureMVC相关
//定义Facade
#define DefFacade__(f,key) \
    using PureMVC::Patterns::IFacade;\
    using PureMVC::Patterns::Facade;\
    IFacade& f = Facade::getInstance(key);\

//传入消息体
#define BodyIn__(body)\
    static_cast<void *>(body)

//读出消息体
#define BodyOut__(dst,dsttype,notify) \
    using namespace NotificationBody;\
    const dsttype dst = static_cast<const dsttype>(notify.getBody());

//验证存在 不存在直接返回
#define AssertExist__(com,x,...)\
    if(not gameFacade.has##com(x))\
    {\
      LOG_FATAL(#com #x" not exist ... return");\
      return __VA_ARGS__;\
    }

//定义组件
#define DefModule__(base,type,var) \
    type& var = dynamic_cast<type&>(gameFacade.retrieve##base(#type))

//验证注册成功日志
#define CHK_REG__(com,x)\
    if(gameFacade.has##com(x))\
    {\
      DLOG_TRACE("register" << #com << " " << #x << " success !");\
    }\
    else\
    {\
      DLOG_TRACE("register" << #com << " " << #x << " failure ...");\
    }


///////////////////////////////////////////////////
//异常处理
#define ERROR(e) \
DLOG_EXCEPT(e); \
RLOG_ERROR << e << endl;

#define __TRY__ \
try\
{

#define __CATCH__ \
} \
catch (const TarsDecodeException& e)\
{\
    ERROR(string("catch tars decode exception : ") + e.what());\
}\
catch (const TarsEncodeException& e)\
{\
    ERROR(string("catch tars encode exception : ") + e.what());\
}\
catch (const TarsProtoException& e)\
{\
    ERROR(string("catch proto exception : ") + e.what());\
}\
catch (const TC_Exception& e)\
{\
    ERROR(string("catch tc exception : ") + e.what());\
}\
catch (const std::exception& e)\
{\
    ERROR(string("catch std exception : ") + e.what());\
}\
catch (...)\
{\
    ERROR("catch unknown exception.");\
};

//编码
template <class structT>
std::vector<char> Encoding(structT const &s)
{
    tars::TarsOutputStream<> jos;
    s.writeTo(jos);
    return jos.getByteBuffer();
}

//解码
template <class structT>
structT Decoding(std::vector<char> msg)
{
    structT t;
    tars::TarsInputStream<> jis;
    jis.setBuffer(msg.data(), msg.size());
    t.readFrom(jis);
    return t;
}

/*
 *通用模板方法：pb对象T序列化
 * @param t 类型T的对象
 * @return 字符串
*/
template<typename T>
std::string pbToString(const T &t)
{
    string s;
    t.SerializeToString(&s);
    return s;
}

template<typename T>
void pbTobuffer(const T &t, vector<char> &buffer)
{
    string s;
    t.SerializeToString(&s);
    buffer.insert(buffer.begin(), s.begin(), s.end());
    return;
}

template<typename T>
vector<char> pbTobuffer(const T &t)
{
    string s;
    t.SerializeToString(&s);
    vector<char> buffer;
    buffer.insert(buffer.begin(), s.begin(), s.end());
    return buffer;
}

/**
 * 通用模板方法: tars对象T结构化
 * @param t 字符串
 * @return 类型T的对象
 */
template<typename T>
T &pbToObj(const std::string &s, T &t)
{
    t.ParseFromString(s);
    return t;
}

template<typename T>
T pbToObj(const vector<char> &vc)
{
    T t;
    string s;
    s.assign(vc.begin(), vc.end());
    t.ParseFromString(s);
    return t;
}

template<typename T>
std::string logPb(const T &t)
{
    std::string str;
    google::protobuf::TextFormat::PrintToString(t, &str);
    return str;
}

template<typename T>
void logPb(const T &t, std::string *str)
{
    google::protobuf::TextFormat::PrintToString(t, str);
}

/**
 * 通用模板方法: tars对象T序列化
 * @param t 类型T的对象
 * @return 字符串
 */
template<typename T>
std::string tostring(const T &t)
{
    string s;
    tars::TarsOutputStream<BufferWriter> osk;
    t.writeTo(osk);
    s.assign(osk.getBuffer(), osk.getLength());

    return s;
}

// 更通用一点
template<typename T>
void tobuffer(const T &t, vector<char> &buffer)
{
    tars::TarsOutputStream<BufferWriter> osk;
    t.writeTo(osk);
    buffer = osk.getByteBuffer();

    return;
}

/**
 * 通用模板方法: tars对象T结构化
 * @param t 字符串
 * @return 类型T的对象
 */
template<typename T>
T &toObj(const std::string &s, T &t)
{
    tars::TarsInputStream<BufferReader> isk;
    isk.setBuffer(s.c_str(), s.length());
    t.readFrom(isk);

    return t;
}

// 通用一点
template<typename T>
T toObj(const vector<char> &vc)
{
    T t;
    tars::TarsInputStream<BufferReader> isk;
    isk.setBuffer((const char *)(&vc[0]), vc.size());
    t.readFrom(isk);

    return t;
}

// 更通用一点
template<typename T, typename B>
T &toObj(const B &vc, T &t)
{
    tars::TarsInputStream<BufferReader> isk;
    isk.setBuffer((const char *)(&vc[0]), vc.size());
    t.readFrom(isk);

    return t;
}

/**
 * 通用模板方法: tars对象T结构化打印
 * @param t 类型T的对象
 * @return 字符串
 */
template<typename T>
std::string printTars(const T &t)
{
    ostringstream os;
    t.display(os);

    return os.str();
}

/**
 * 通用模板方法: tars对象容器结构化打印
 * @param itbegin  容器的iterator begin
 * @param itend  容器的iterator end
 * @return 字符串
 */
template <typename I>
std::string printTars(I itbegin, I itend)
{
    std::ostringstream s;
    I it = itbegin;
    while(it != itend)
    {
        it->display(s);
        ++it;
    }

    return s.str();
}

/**
 * 通用模板方法: tars对象T单行日志化打印
 * @param t 类型T的对象
 * @return 字符串
 */
template<typename T>
std::string logTars(const T &t)
{
    ostringstream os;
    t.displaySimple(os);

    return os.str();
}

/**
 * 通用模板方法: Tars对象T单行日志化打印
 * @param t 类型T的对象
 * @param sep 替换分隔符
 * @return 字符串
 */
template<typename T>
std::string logTars(const T &t, const string &sep)
{
    ostringstream os;
    t.displaySimple(os);

    return TC_Common::replace(os.str(), "|", sep.c_str());
}

/**
 * 通用模板方法: tars对象容器日志化打印
 * @param itbegin  容器的iterator begin
 * @param itend  容器的iterator end
 * @return 字符串
 */
template <typename I>
std::string logTars(I itbegin, I itend)
{
    std::ostringstream s;
    I it = itbegin;
    while(it != itend)
    {
        it->displaySimple(s);
        s << ";";
        ++it;
    }

    return s.str();
}

#endif /*__COMMON_MACROS_H__*/
