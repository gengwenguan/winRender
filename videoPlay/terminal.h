/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  terminal.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  �ն��࣬�ڲ������������h264������ffmpeg����h264���ݡ�SDL��ȾYUV����
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

    //�ͻ������� serverAddress ��������ip��ַ
    int Run(std::string serverAddress);

    //ֹͣ�ͻ�������
    int Stop();
private:
    //tcp�ͻ��˴�������յ�h264�����ͽ���������
    int OnRecvData(char* data, int dataLen) override;

    //�ӽ������ص��Ľ�����YUV����
    int OnYuvData(AVFrame* frame) override;

private:
    C_TcpClient  m_TcpClient;
    C_H264Decode m_H264Decode;
    C_YuvRender  m_YuvRender;
};