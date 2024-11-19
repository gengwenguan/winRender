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

//客户端运行 serverAddress 服务器的ip地址
int C_Terminal::Run(std::string serverAddress)
{
	return m_TcpClient.Run(serverAddress);
}

//客户端运行 serverAddress 服务器的ip地址
int C_Terminal::Stop()
{
	return m_TcpClient.Stop();
}

//tcp客户端从网络接收的h264数据送解码器解码
int C_Terminal::OnRecvData(char* data, int dataLen)
{
	return m_H264Decode.Decode(data, dataLen);
}

//从解码器回调的解码后的额YUV数据
int C_Terminal::OnYuvData(AVFrame* frame)
{
	m_YuvRender.Render(frame);
	return 0;
}

//获取最后一次用户输入的ip地址，同时也存储用户最后输入的ip地址
std::string  C_Terminal::GetStorageIp()
{
    std::string filename = "ipaddress.cfg"; // 存储ip地址的文件名
    std::string storageIpaddr;              // 从文件中读取到的ip地址

    // 读取文件内容
    std::ifstream infile(filename);
    if (infile.is_open()) {
        getline(infile, storageIpaddr);     // 从文件中将ip地址读取出来
        infile.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }

    std::cout << "Please input server ip ,if not input default ip=" << storageIpaddr << " server ip:";

    //获取用户输入的服务器IP地址
    std::string ipaddr;
    //std::cin >> ipaddr;
    // 读取一行输入内容
    std::getline(std::cin, ipaddr);
    if (ipaddr.length() == 0) {
        ipaddr = storageIpaddr; //用户没有输入ip时默认使用配置文件中的ip地址
    }

    std::cout << "Connect Server ip:" << ipaddr << std::endl;

    // 更新配置文件中的ip地址为最后输入的ip地址
    std::ofstream outfile(filename);  // 默认模式是覆盖写入
    if (outfile.is_open()) {
        outfile << ipaddr;
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }

    return ipaddr;
}