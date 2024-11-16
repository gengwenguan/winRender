/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  yuvRender.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  SDL��ȾYUV����,YUV�ֱ��ʱ仯ʱ��̬֧��ˢ�´��ڴ�С
**********************************************************************************/
#pragma once
#include <string>
#include "SDL.h"
#include "libavutil/frame.h"

class C_YuvRender
{
public:
    C_YuvRender();
    ~C_YuvRender();

    //��Ⱦһ֡YUV����
    int Render(AVFrame* frame);

private:
    //YUV���ݷֱ��ʱ仯ʱˢ�´��ڴ�С��ƵYUV���ݷֱ���
    void RefreshWindowSize(int width, int height);

private:
    int    m_width;  //��Ⱦ���ڵĿ��
    int    m_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};