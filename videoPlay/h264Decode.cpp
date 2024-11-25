#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "h264Decode.h"

C_H264Decode::C_H264Decode(C_Listener* pListener)
	:m_pListener(pListener)
{
    // 找到解码器
    m_codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!m_codec) {
        std::cerr << "Codec not found" << std::endl;
        return ;
    }

    // 打开解码器
    m_codec_context = avcodec_alloc_context3(m_codec);
    if (!m_codec_context) {
        std::cerr << "Could not allocate codec context" << std::endl;
        return ;
    }

    if (avcodec_open2(m_codec_context, m_codec, NULL) < 0) {
        std::cerr << "Could not open codec" << std::endl;
        return ;
    }

    // 分配帧和包
    m_frame = av_frame_alloc();
    if (!m_frame) {
        std::cerr << "Could not allocate frame" << std::endl;
        return ;
    }
    m_packet = av_packet_alloc();
    //av_init_packet(m_packet);

}

C_H264Decode::~C_H264Decode()
{
    // 清理资源
    av_frame_free(&m_frame);
    av_packet_free(&m_packet);
    avcodec_free_context(&m_codec_context);
}

int C_H264Decode::Decode(char* data, int dataLen)
{
    m_packet->size = dataLen;
    m_packet->data = (uint8_t*)data;

    int ret = avcodec_send_packet(m_codec_context, m_packet);
    if (ret < 0) {
        std::cerr << "Error sending a packet for decoding ret:%d" << ret << std::endl;
        return -1;
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(m_codec_context, m_frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        }
        else if (ret < 0) {
            std::cerr << "Error during decoding" << std::endl;
            break;
        }

        //std::cout << "w=" << m_frame->width << "  h=" << m_frame->height 
        //    << "linesize[0] =" << m_frame->linesize[0] 
        //    << "linesize[1] =" << m_frame->linesize[1]
        //    << "linesize[2] =" << m_frame->linesize[2]
        //    << std::endl;
        m_pListener->OnYuvData(m_frame);


        // 示例：保存YUV420数据到文件
        //static int frame_count = 0;
        //std::string filename = "frame_" + std::to_string(frame_count++) + ".yuv";
        //std::ofstream yuv_file(filename, std::ios::binary);
        //if (!yuv_file) {
        //    std::cerr << "Could not open file for writing: " << filename << std::endl;
        //    continue;
        //}

        //// 写入YUV数据
        //for (int i = 0; i < m_frame->height; i++) {
        //    yuv_file.write((const char*)(m_frame->data[0] + m_frame->linesize[0] * i), m_frame->width);
        //}
        //for (int i = 0; i < m_frame->height / 2; i++) {
        //    yuv_file.write((const char*)(m_frame->data[1] + m_frame->linesize[1] * i), m_frame->width / 2);
        //}
        //for (int i = 0; i < m_frame->height / 2; i++) {
        //    yuv_file.write((const char*)(m_frame->data[2] + m_frame->linesize[2] * i), m_frame->width / 2);
        //}

        //yuv_file.close();
    }
	return 0;
}

