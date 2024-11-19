#include <fstream>
#include"terminal.h"
#include<iostream>
C_Terminal::C_Terminal()
	:m_TcpClient(this),
	m_H264Decode(this),
	m_YuvRender()
{

}
C_Terminal::~C_Terminal()
{

}

//�ͻ������� serverAddress ��������ip��ַ
int C_Terminal::Run(std::string serverAddress)
{
	return m_TcpClient.Run(serverAddress);
}

//�ͻ������� serverAddress ��������ip��ַ
int C_Terminal::Stop()
{
	return m_TcpClient.Stop();
}

//tcp�ͻ��˴�������յ�h264�����ͽ���������
int C_Terminal::OnRecvData(char* data, int dataLen)
{
	return m_H264Decode.Decode(data, dataLen);
}

//�ӽ������ص��Ľ����Ķ�YUV����
int C_Terminal::OnYuvData(AVFrame* frame)
{
	m_YuvRender.Render(frame);
	return 0;
}

//��ȡ���һ���û������ip��ַ��ͬʱҲ�洢�û���������ip��ַ
std::string  C_Terminal::GetStorageIp()
{
    std::string filename = "ipaddress.cfg"; // �洢ip��ַ���ļ���
    std::string storageIpaddr;              // ���ļ��ж�ȡ����ip��ַ

    // ��ȡ�ļ�����
    std::ifstream infile(filename);
    if (infile.is_open()) {
        getline(infile, storageIpaddr);     // ���ļ��н�ip��ַ��ȡ����
        infile.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }

    std::cout << "Please input server ip ,if not input default ip=" << storageIpaddr << " server ip:";

    //��ȡ�û�����ķ�����IP��ַ
    std::string ipaddr;
    //std::cin >> ipaddr;
    // ��ȡһ����������
    std::getline(std::cin, ipaddr);
    if (ipaddr.length() == 0) {
        ipaddr = storageIpaddr; //�û�û������ipʱĬ��ʹ�������ļ��е�ip��ַ
    }

    std::cout << "Connect Server ip:" << ipaddr << std::endl;

    // ���������ļ��е�ip��ַΪ��������ip��ַ
    std::ofstream outfile(filename);  // Ĭ��ģʽ�Ǹ���д��
    if (outfile.is_open()) {
        outfile << ipaddr;
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }

    return ipaddr;
}