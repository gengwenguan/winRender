/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  tcpClient.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  TCP�ͻ����࣬����TCP server������server������h264����
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
        /*�¿ͻ��������¼�*/
        virtual int OnRecvData(char* data, int dataLen) = 0;
    };

public:
	C_TcpClient(C_Listener* pListener);
	~C_TcpClient();

    //�ͻ������� serverAddress ��������ip��ַ
    int Run(std::string serverAddress);

    //ֹͣ�ͻ�������
    int Stop();

private:
    
    C_Listener* m_pListener;
    bool        m_bRun;
};