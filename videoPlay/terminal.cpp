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