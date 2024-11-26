视频监控项目Windows取流客户端
=========
适用场景
---------
该windows工程为https://github.com/gengwenguan/libmaix 摄像头监控程序提供网络预览回放等功能

底层依赖
---------
该为vs2019创建工程，集成了ffmpeg库解码h264，集成SDL库进行视频渲染

目录介绍
---------
    dep：依赖的ffmpeg库和SDL库
    videoPlay：程序代码路径，其中包括网络数据接收，视频解码，视频渲染等代码逻辑
    x64: 其中relese目录下为可执行文件路径，双击videoPlay.exe文件运行
