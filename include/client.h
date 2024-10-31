#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#pragma comment(lib, "ws2_32.lib") // 链接 Winsock 库
namespace msg_fsonar
{
    struct Obj
    {
        std::string msg;
        float center_x;
        float center_y;
        float distance_x;
        float distance_y;
    };
}


class client
{
private:
    /* data */
public:
    SOCKET sock;
    client(std::string IP,int port);
    void sendmessage(std::vector<msg_fsonar::Obj>& vec);
    ~client();
};
