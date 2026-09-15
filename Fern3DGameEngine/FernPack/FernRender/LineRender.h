#pragma once


namespace Fern {
    class LineRender {
    public:
        /**
         * 使用 Bresenham 算法绘制一条直线
         * @param window   Window 对象指针，用于绘制像素
         * @param x0, y0   起点坐标
         * @param x1, y1   终点坐标
         * @param color    直线颜色
         * @deprecated 新版函数实现应该：支持直接读取屏幕坐标，支持深度绘制
         */
        static void DrawLine(Window* window, int x0, int y0, int x1, int y1, const Color& color) {
            // 如果窗口为空，直接返回
            if (!window) return;

            // ---------- Bresenham 核心算法 ----------
            int dx = x1 > x0 ? x1 - x0 : x0 - x1;
            int dy = y1 > y0 ? y1 - y0 : y0 - y1;
            int sx = (x0 < x1) ? 1 : -1; // x 方向步长
            int sy = (y0 < y1) ? 1 : -1; // y 方向步长
            int err = dx - dy;           // 初始误差项

            while (true) {
                // 绘制当前点
                DrawPixel(x0, y0, -1.0, color, false);

                // 到达终点，退出循环
                if (x0 == x1 && y0 == y1) break;

                int e2 = 2 * err;
                // 调整 x 和 y 坐标，步进直线
                if (e2 > -dy) {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y0 += sy;
                }
            }

            std::ostringstream oss;
            oss << "已从点 (" << x0 << "," << y0 << ") 向 (" << x1 << "," << y1 << ") 绘制直线，直线颜色为" << color.getARGB();
            std::string msg = oss.str();
            LOG_INFO(msg);
        }

        static void DrawLine(Window* window, const Fern::Vector3D& start, const Fern::Vector3D& end, const Color& color) {
            if (!window) return;

            // 1. 四舍五入为整数坐标
            int x0 = (int)(start.x );
            int y0 = (int)(start.y );
            int x1 = (int)(end.x );
            int y1 = (int)(end.y );

            float z0 = start.z;
            float z1 = end.z;

            // 2. 如果起点和终点相同，直接绘制一个点
            if (x0 == x1 && y0 == y1) {
                DrawPixel(x0, y0, (z0 < z1 ? z0 : z1), color);
                return;
            }

            // 3. Bresenham 算法
            int dx = x1 > x0 ? x1 - x0 : x0 - x1;
            int dy = y1 > y0 ? y1 - y0 : y0 - y1;
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            int curx = x0, cury = y0;
            double curdepth;

            // 计算深度增量（根据总步数）


            while (true) {
                //插值计算深度
                curdepth = Math::insert(z0, z1, Math::getInsertNumber(start.x, end.x, curx));

                // 绘制当前点（使用插值后的深度）
                DrawPixel(curx, cury, curdepth-0.05f, color, false);

                // 到达终点，退出循环
                if (curx == x1 && cury == y1) break;

                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    curx += sx;

                }
                if (e2 < dx) {
                    err += dx;
                    cury += sy;

                }
            }

            // 日志
            std::ostringstream oss;
            oss << "已从点 (" << x0 << "," << y0 << ") 向 (" << x1 << "," << y1 << ") 绘制直线，直线颜色为" << color.getARGB();
            LOG_INFO(oss.str());
        }

        /**
         * @brief 绘制带深度的 3D 直线
         * @param window  窗口对象
         * @param start   起点（屏幕坐标 + 深度值）
         * @param end     终点（屏幕坐标 + 深度值）
         * @param color   颜色
         */
        static void DrawLine3D(Window* window, const Vector3D& start, const Vector3D& end, const Color& color) {
            if (!window) return;

            // 1. 将浮点数坐标四舍五入为整数（窗口坐标必须为整数）
            int x0 = (int)(start.screenx);
            int y0 = (int)(start.screeny );
            int x1 = (int)(end.screenx );
            int y1 = (int)(end.screeny );

            float z0 = start.screendepth;  // 深度值
            float z1 = end.screendepth;

            // 2. 如果起点和终点相同，直接绘制一个点
            if (x0 == x1 && y0 == y1) {
                DrawPixel(x0, y0, z0, color);
                return;
            }

            // 3. Bresenham 算法初始化
            int dx = x1 > x0 ? x1 - x0 : x0 - x1;
            int dy = y1 > y0 ? y1 - y0 : y0 - y1;
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;

            int curx = x0, cury = y0;

            // 4. 计算深度增量（总步数）
            int steps = dx > dy ? dx : dy;
            float dz = steps > 0 ? (z1 - z0) / steps : 0.0f;
            float curdepth = z0;

            while (true) {
                // 绘制当前像素（带深度测试）
                DrawPixel(curx, cury, curdepth, color);

                // 到达终点
                if (curx == x1 && cury == y1) break;

                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    curx += sx;
                    curdepth += dz;  // 深度值随 x 步进
                }
                if (e2 < dx) {
                    err += dx;
                    cury += sy;
                    curdepth += dz;  // 深度值随 y 步进
                }
            }
        }

    };

}