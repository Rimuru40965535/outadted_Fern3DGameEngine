// Samples/01_BlackWindow/main.cpp
#include "../FernCore/Window.h"
#include "../Log/LogBuff.h"
#include <iostream>

int main() {
    Fern::LogBuff::onlyLogInstance().start("app.log");

    // 创建一个 800x600 的窗口，标题为 "Fern Engine - Black Window"
    Fern::Window window(800, 600, "Fern Engine - Black Window");

    LOG_INFO("窗口已创建，按ESC退出。");

    // 主循环
    while (!window.ShouldClose()) {
        // 1. 处理事件（目前为空）
        window.PollEvents();

        // 2. 清屏（黑色）
        window.Clear();

        // 3. 将后台缓冲区绘制到屏幕
        window.Present();

        // 4. 简单延时，降低 CPU 占用
        Sleep(10); // EasyX 中可以使用 Sleep
    }

    LOG_INFO("窗口已关闭");

    Fern::LogBuff::onlyLogInstance().stop();

    return 0;
}