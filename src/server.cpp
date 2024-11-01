#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#pragma comment(lib, "ws2_32.lib") // 链接 Winsock 库

#define PORT 1101

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



int main() 
{
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    msg_fsonar::Obj m_obj;
    // char buffer[1024] = {0};

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // 创建 socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    // 设置地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定 socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // 监听
    if (listen(server_socket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    // 接受连接
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len)) == INVALID_SOCKET) {
        std::cerr << "Accept failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }
    

    while (true)
    {
        std::cout << "111" << std::endl;
        // 接收 vector 的大小
        int net_size;
        int byte =recv(client_socket, (char*)&net_size, sizeof(net_size), 0);
        std::cout<<"byte = "<<byte<<std::endl;
        if (byte>0)
        {
            int size = ntohl(net_size); // 转换为主机字节序
            std::vector<msg_fsonar::Obj> vec(size);
            // 接收 vector 的内容
            recv(client_socket, reinterpret_cast<char*>(vec.data()), size * sizeof(msg_fsonar::Obj), 0);
            // 处理接收到的数据
            for (const auto& obj : vec)
            {
                // 处理每个 obj
                // 例如：打印数据
                printf("msg: %.4s, center_x: %f, center_y: %f, distance_x: %f, distance_y: %f\n",
                    obj.msg, obj.center_x, obj.center_y, obj.distance_x, obj.distance_y);
            }
        }
        






        // char buffer[sizeof(msg_fsonar::Obj)] = {0};
        // // 读取数据
        // int byte=recv(client_socket, buffer, sizeof(msg_fsonar::Obj), 0);
        // std::cout << "size of message: " << byte << std::endl;
        // memcpy(&m_obj, buffer, sizeof(msg_fsonar::Obj));
        // std::cout << "distcane_y: " << m_obj.distcane_y << std::endl;
        //std::cout << "Message from client: " << buffer << std::endl;
       
        // // 发送回应
        // const char* response = "Hello from server";
        // send(client_socket, response, strlen(response), 0);
    }
    
    // 关闭 socket
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
