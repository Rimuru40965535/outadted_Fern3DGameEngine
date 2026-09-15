#include "../FernCore/Window.h"
#include "../FernCore/Color.h"
#include "../FernRender/LineRender.h"

#define LOG_BUFF_SETTINGS_MINIMUM_LEVEL Fern::Level::APPEND
#include "../Log/LogBuff.h"

int main() {
    LOG_INSTANCE.start("app.log");

    int window_width = 800;
    int window_height = 600;
    // 创建窗口
    Fern::Window window(window_width, window_height, "Fern Engine - Line Test");
    LOG_INFO("开始画线测试...");

    // 清空背景为黑色
    window.Clear();
    window.Present(); // 先刷新一次，显示黑底

    // 使用 LineRenderer 绘制多条测试直线

    // 1. 对角线 (白色)
    Fern::LineRenderer::DrawLine(&window, 50, 50, 750, 550, Fern::Color::White());

    // 2. 水平线 (红色)
    Fern::LineRenderer::DrawLine(&window, 100, 100, 700, 100, Fern::Color::Red());

    // 3. 垂直线 (绿色)
    Fern::LineRenderer::DrawLine(&window, 400, 50, 400, 550, Fern::Color::Green());

    // 4. 斜线 (蓝色)
    Fern::LineRenderer::DrawLine(&window, 100, 500, 700, 150, Fern::Color::Blue());

    // 刷新显示
    window.Present();
    LOG_INFO("画线完成，按 ESC 退出...");

    // 等待退出
    while (!window.ShouldClose()) {
        window.PollEvents();
        Sleep(10);
    }

    LOG_INSTANCE.stop();
    return 0;
}