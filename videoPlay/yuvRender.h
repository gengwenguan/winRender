/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:  yuvRender.h
  *Author:    gengwenguan
  *Date:      2024-11-16
  *Description:  SDL渲染YUV数据,YUV分辨率变化时动态支持刷新窗口大小
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

    //渲染一帧YUV数据
    int Render(AVFrame* frame);

private:
    //YUV数据分辨率变化时刷新窗口大小视频YUV数据分辨率
    void RefreshWindowSize(int width, int height);

private:
    int    m_width;  //渲染窗口的宽高
    int    m_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};