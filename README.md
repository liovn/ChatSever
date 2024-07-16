# ChatSever
可以在多台服务器上的tcp集群通信的服务器项目代码。使用muduo，redis，mysql，nginx，json..等

编译
cd build
cmake ..
make

服务器运行
需要nginx 负载均衡
cd bin
./ChatSever 127.0.0.1 6000
./ChatSever 127.0.0.1 6002
nginx可以在多台服务器上运行

客户端运行
cd bin 
./ChatSerivce 127.0.0.1 8000



集群通信网络服务器平台
应用技术：C/C++，Json，Muduo、MySQL，Redis，Nginx
项目描述：基于 muduo 网络库开发的集群通信平台，具有注册、登录、一对一、群组通信等业务功能。
主要工作：1、项目包括网络 I/O 模块，通信业务模块，数据模块，通过函数的绑定和回调，降低模块之间的耦合度。
2、使用 json 对消息进行序列化和反序列化，基于 muduo 库对消息进行网络 I/O 传输。
3、使用 mysql 数据库作为项目数据的落地存储，基于 redis 的发布订阅功能，实现跨服务器的消息通信。
4、配置 nginx 基于 tcp 的负载均衡，提高集群通信的并发能力。
