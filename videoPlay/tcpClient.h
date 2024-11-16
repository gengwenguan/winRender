/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  tcpClient.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  TCP客户端类，连接TCP server，接收server发来的h264裸流
**********************************************************************************/
#pragma once
#include <string>

class C_TcpClient
{
public:
    class C_Listener
    {
    public:
        virtual ~C_Listener() = default;
        /*新客户端连接事件*/
        virtual int OnRecvData(char* data, int dataLen) = 0;
    };

public:
	C_TcpClient(C_Listener* pListener);
	~C_TcpClient();

    //客户端运行 serverAddress 服务器的ip地址
    int Run(std::string serverAddress);

    //停止客户端运行
    int Stop();

private:
    
    C_Listener* m_pListener;
    bool        m_bRun;
};