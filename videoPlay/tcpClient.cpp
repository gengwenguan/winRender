#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdint>
#include <memory>
#include"tcpClient.h"
#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 56050

C_TcpClient::C_TcpClient(C_Listener* pListener)
    :m_pListener(pListener)
{
}

C_TcpClient::~C_TcpClient()
{
}

//停止客户端运行
int C_TcpClient::Stop()
{
    m_bRun = false;
    return 0;
}

int C_TcpClient::Run(std::string serverAddress)
{
    m_bRun = true;
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in serverAddr;

    std::unique_ptr<char[]> recvBuffer(new char[1024 * 100]); //1M的接收缓冲区
    int result;

    // 初始化 Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // 创建套接字
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

    // 连接服务器
    result = connect(ConnectSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    // 循环接收数据
    while (m_bRun) {
        uint32_t dataLength;

        // 接收4字节的数据长度
        result = recv(ConnectSocket, (char*)&dataLength, sizeof(dataLength), 0);
        if (result == SOCKET_ERROR) {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            break;
        }

        dataLength = ntohl(dataLength); // 将网络字节序转换为主机字节序

        //std::cout << "Received data length: " << dataLength << std::endl;

        // 接收实际数据
        uint32_t totalBytesReceived = 0;
        while (totalBytesReceived < dataLength) {
            result = recv(ConnectSocket, recvBuffer.get() + totalBytesReceived, dataLength - totalBytesReceived, 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
                return -1;
            }
            totalBytesReceived += result;
        }

        if (m_pListener != nullptr) {
            //网络接收数据向上回调
            m_pListener->OnRecvData(recvBuffer.get(), dataLength);
        }

        // 处理接收到的数据
        //recvBuffer[result] = '\0'; // 为了安全起见，添加终止符
        //std::cout << "Received data: " << recvBuffer << std::endl;
    }

    // 关闭套接字并清理 Winsock
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
