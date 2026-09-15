/**
 * @file Fern3DEngine/FernRender/RenderCommand.h
 *
 * @brief 渲染命令队列
 * @details
 * 该模块执行渲染命令的队列（先入先出）缓冲。
 *

 *
 * @author 半人马座beta星
 * @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
 * @date 2026/8/4
 */

#pragma once

namespace Fern::RenderCommand {
    class Queue {
    private:
        std::queue<Fern::RenderCommand::Command> queue;
        std::mutex mtx;
        std::condition_variable cv;
        bool stopped = false;

    public:
        Queue() {}

        void Push(const Command& cmd) {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push(cmd);
            cv.notify_one();
        }

        bool Pop(Command& cmd) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !queue.empty() || stopped; });
            if (stopped && queue.empty()) return false;
            cmd = queue.front();
            queue.pop();
            return true;
        }

        void Stop() {
            std::lock_guard<std::mutex> lock(mtx);
            stopped = true;
            cv.notify_all();
        }
    };

    
    

    
}