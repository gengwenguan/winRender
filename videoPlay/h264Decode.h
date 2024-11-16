/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  tcpClient.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  h264�����࣬ʹ��ffmpeg��h264����ΪYUV420����
**********************************************************************************/
#pragma once
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

class C_H264Decode
{
public:
    class C_Listener
    {
    public:
        virtual ~C_Listener() = default;
        /*�¿ͻ��������¼�*/
        virtual int OnYuvData(AVFrame* frame) = 0;
    };

public:
    C_H264Decode(C_Listener* pListener);
    ~C_H264Decode();

    //�ͻ������� serverAddress ��������ip��ַ
    int Decode(char* data, int dataLen);

private:
    C_Listener*      m_pListener;
    const AVCodec*   m_codec;
    AVCodecContext*  m_codec_context;
    AVFrame*         m_frame;
    AVPacket*        m_packet;
};