// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>    // 包含线程库
#include <chrono>    // 包含时间库
#include <fstream>

#include "SDL.h"
#include "terminal.h"

#if 1
int main(int argc, char* argv[])
{
    //获取存储的ip地址
    std::string ipaddr = C_Terminal::GetStorageIp();

    C_Terminal* terminal = new C_Terminal();
    //在新起的线程中接收网络数据解码渲染
    std::thread mythread([terminal, ipaddr]() { terminal->Run(ipaddr); });

    // 监听退出事件
    SDL_Event event;
    bool brun = true;
    do {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            brun = false;  //退出程序
            break;
        default:
            //SDL_Log("event.type=%d", event.type);
            break;
        }

    } while (brun);

    //停止终端接收网络数据，让线程退出
    terminal->Stop();
    //回收线程资源
    mythread.join();

    delete terminal;

    return 0;
}
#endif


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
