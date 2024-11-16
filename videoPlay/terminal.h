/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  terminal.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  终端类，内部集成网络接收h264裸流、ffmpeg解码h264数据、SDL渲染YUV数据
**********************************************************************************/
#pragma once
#include <string>
#include"h264Decode.h"
#include"tcpClient.h"
#include"yuvRender.h"

class C_Terminal : public C_TcpClient::C_Listener,
                   public C_H264Decode::C_Listener
{
public:
    C_Terminal();
    ~C_Terminal();

    //客户端运行 serverAddress 服务器的ip地址
    int Run(std::string serverAddress);

    //停止客户端运行
    int Stop();
private:
    //tcp客户端从网络接收的h264数据送解码器解码
    int OnRecvData(char* data, int dataLen) override;

    //从解码器回调的解码后的YUV数据
    int OnYuvData(AVFrame* frame) override;

private:
    C_TcpClient  m_TcpClient;
    C_H264Decode m_H264Decode;
    C_YuvRender  m_YuvRender;
};