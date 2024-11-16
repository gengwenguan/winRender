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
    std::string filename = "ipaddress.cfg"; // 存储ip地址的文件名
    std::string storageIpaddr;              // 从文件中读取到的ip地址

    // 读取文件内容
    std::ifstream infile(filename);
    if (infile.is_open()) {
        getline(infile, storageIpaddr);     // 从文件中将ip地址读取出来
        infile.close();
    }
    else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }

    std::cout << "Please input server ip ,if not input default ip=" << storageIpaddr << " server ip:";

    //获取用户输入的服务器IP地址
    std::string ipaddr;
    //std::cin >> ipaddr;
    // 读取一行输入内容
    std::getline(std::cin, ipaddr);
    if (ipaddr.length() == 0) {
        ipaddr = storageIpaddr; //用户没有输入ip时默认使用配置文件中的ip地址
    }

    std::cout << "Connect Server ip:" << ipaddr << std::endl;

    // 更新配置文件中的ip地址为最后输入的ip地址
    std::ofstream outfile(filename);  // 默认模式是覆盖写入
    if (outfile.is_open()) {
        outfile << ipaddr;
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
    //!!!! 以上内容只是为了记录最后一次输入的ip地址避免多次连接同一服务器设备时重复输入的问题

    
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
