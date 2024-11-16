#include"yuvRender.h"

C_YuvRender::C_YuvRender()
    :m_width(240),  //默认创建240*240分辨率窗口
    m_height(240)   //后续解码输出YUV分辨率发生变化时
{
    // 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL 初始化失败: %s\n", SDL_GetError());
        return ;
    }

    // 创建窗口
    window = SDL_CreateWindow("SDL YUV Render", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_width, m_height, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "创建窗口失败: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "创建渲染器失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // 创建纹理
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
        m_width, m_height);
    if (!texture) {
        fprintf(stderr, "创建纹理失败: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

C_YuvRender::~C_YuvRender()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//YUV数据分辨率变化时刷新窗口大小视频YUV数据分辨率
void C_YuvRender::RefreshWindowSize(int width, int height)
{
    m_width = width; m_height = height;

    //调整渲染窗口大小
    SDL_SetWindowSize(window, m_width, m_height);

    //销毁纹理和渲染器
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "创建渲染器失败: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // 创建纹理
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
        m_width, m_height);
    if (!texture) {
        fprintf(stderr, "创建纹理失败: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

//渲染一帧YUV数据
int C_YuvRender::Render(AVFrame* frame)
{
    //解码输出的YUV分辨率变化时，调整渲染窗口大小视频YUV分辨率
    if (frame->width != m_width || frame->height != m_height)
    {
        RefreshWindowSize(frame->width, frame->height);
    }

    // 渲染一帧
    //SDL_UpdateYUVTexture(texture, nullptr, yPlane, SCREEN_WIDTH, uPlane, SCREEN_WIDTH / 2, vPlane, SCREEN_WIDTH / 2);
    SDL_UpdateYUVTexture(texture, nullptr, frame->data[0], frame->linesize[0], frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);

    // 清空渲染器
    SDL_RenderClear(renderer);

    // 拷贝纹理到渲染器
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // 显示渲染器
    SDL_RenderPresent(renderer);
    return 0;
}