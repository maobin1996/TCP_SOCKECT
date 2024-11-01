/*客户端，forward_sonar*/
#include <iostream>
#include "client.h"
#include <winsock2.h>
#include <ws2tcpip.h>



#define PORT 1101

client::client(std::string IP,int port)
{
    std::cout<<"IP:"<<IP<<" port:"<<port<<std::endl;
    WSADATA wsaData;
    //SOCKET sock;
    //msg_fsonar::Obj m_obj;
    struct sockaddr_in server_addr;
    const char* message = "Hello from client";
    // char buffer[1024] = {0};

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
    }

    // 创建 socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << std::endl;
        WSACleanup();
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // 将 IP 地址转换为二进制形式

    // 连接到服务端
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
    }

}

void client::sendmessage(std::vector<msg_fsonar::Obj>& vec)
{
    int  size = vec.size();
    int net_size = htonl(size);
    // 发送vector的大小
    send(sock, (char*)&net_size, sizeof(net_size), 0);
    // 发送vector的内容
    send(sock,reinterpret_cast<char*>(vec.data()), size * sizeof(msg_fsonar::Obj), 0);
}

client::~client()
{
    closesocket(sock);
    WSACleanup();
}

#ifdef false

int main()
{
    WSADATA wsaData;
    SOCKET sock;
    msg_fsonar::Obj m_obj;
    struct sockaddr_in server_addr;
    const char* message = "Hello from client";
    // char buffer[1024] = {0};

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // 创建 socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error" << std::endl;
        WSACleanup();
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // 将 IP 地址转换为二进制形式

    // 连接到服务端
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    while (true)
    {
        // 发送消息
        m_obj.msg = "$FSP";
        m_obj.center_x = 5.1;
        m_obj.center_y =  5.2;
        m_obj.distance_x = 8.1;
        m_obj.distane_y =8.2;
        //std::cout << "size of message: " << sizeof(m_obj) << std::endl;
        char buffer[sizeof(m_obj)];
        memcpy(buffer, &m_obj, sizeof(m_obj));  
        int byte = send(sock, buffer, sizeof(buffer), 0);
        std::cout << "size of message: " << byte << std::endl;
        // std::cout << "Message sent: " << message << std::endl;
        // 接收回应
        // recv(sock, buffer, sizeof(buffer), 0);
        // std::cout << "Message from server: " << buffer << std::endl;
    }
   

    // 关闭 socket
    closesocket(sock);
    WSACleanup();
    return 0;
}

#endif