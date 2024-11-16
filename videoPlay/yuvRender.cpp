#include"yuvRender.h"

C_YuvRender::C_YuvRender()
    :m_width(240),  //Ĭ�ϴ���240*240�ֱ��ʴ���
    m_height(240)   //�����������YUV�ֱ��ʷ����仯ʱ
{
    // ��ʼ�� SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL ��ʼ��ʧ��: %s\n", SDL_GetError());
        return ;
    }

    // ��������
    window = SDL_CreateWindow("SDL YUV Render", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        m_width, m_height, SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "��������ʧ��: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // ������Ⱦ��
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "������Ⱦ��ʧ��: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // ��������
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
        m_width, m_height);
    if (!texture) {
        fprintf(stderr, "��������ʧ��: %s\n", SDL_GetError());
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

//YUV���ݷֱ��ʱ仯ʱˢ�´��ڴ�С��ƵYUV���ݷֱ���
void C_YuvRender::RefreshWindowSize(int width, int height)
{
    m_width = width; m_height = height;

    //������Ⱦ���ڴ�С
    SDL_SetWindowSize(window, m_width, m_height);

    //�����������Ⱦ��
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    // ������Ⱦ��
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "������Ⱦ��ʧ��: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // ��������
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
        m_width, m_height);
    if (!texture) {
        fprintf(stderr, "��������ʧ��: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

//��Ⱦһ֡YUV����
int C_YuvRender::Render(AVFrame* frame)
{
    //���������YUV�ֱ��ʱ仯ʱ��������Ⱦ���ڴ�С��ƵYUV�ֱ���
    if (frame->width != m_width || frame->height != m_height)
    {
        RefreshWindowSize(frame->width, frame->height);
    }

    // ��Ⱦһ֡
    //SDL_UpdateYUVTexture(texture, nullptr, yPlane, SCREEN_WIDTH, uPlane, SCREEN_WIDTH / 2, vPlane, SCREEN_WIDTH / 2);
    SDL_UpdateYUVTexture(texture, nullptr, frame->data[0], frame->linesize[0], frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);

    // �����Ⱦ��
    SDL_RenderClear(renderer);

    // ����������Ⱦ��
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // ��ʾ��Ⱦ��
    SDL_RenderPresent(renderer);
    return 0;
}