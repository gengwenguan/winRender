#include"terminal.h"

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