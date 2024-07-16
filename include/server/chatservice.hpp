#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpServer.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <memory>
#include "json.hpp"
#include "redis.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "offlineMsgModel.hpp"
#include "usermodel.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

//处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

//聊天服务业务类
class ChatService{
public:
    //获取单例对象的接口函数
    static ChatService* instance();
    //登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp);
    //注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr& conn);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 服务器异常，业务重置方法
    void reset();
    
    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int, string);


private:
    ChatService();//构造函数私有化
    
    //存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
    //存储在线用户的通讯连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    //定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    //数据操作类对象
    usermodel _usermodel;
    OfflineMsgModel _offlineMshModel;   
    FriendModel _friendModel;
    GroupModel _groupModel;

    //Redis操作对象
    Redis _redis;
    
};


#endif