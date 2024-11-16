/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  tcpClient.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  h264解码类，使用ffmpeg将h264解码为YUV420数据
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
        /*新客户端连接事件*/
        virtual int OnYuvData(AVFrame* frame) = 0;
    };

public:
    C_H264Decode(C_Listener* pListener);
    ~C_H264Decode();

    //客户端运行 serverAddress 服务器的ip地址
    int Decode(char* data, int dataLen);

private:
    C_Listener*      m_pListener;
    const AVCodec*   m_codec;
    AVCodecContext*  m_codec_context;
    AVFrame*         m_frame;
    AVPacket*        m_packet;
};