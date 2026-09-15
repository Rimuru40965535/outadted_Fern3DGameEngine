/**
 * @file Fern3DEngine/FernRender/Render.h
 *
 * @brief 基础渲染操作
 * @details
 * 
 *
 *
 * @author 半人马座beta星
 * @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
 * @date 2026/7/24
 */

#pragma once


namespace Fern {
	class Render{
	public:
		Fern::Window* window;
		Fern::Camera* camera;
		Fern::DepthBuff* depthBuff;


	public:
		Render(Fern::Window* w, Fern::Camera* c, Fern::DepthBuff* d) :window(w), camera(c), depthBuff(d) {}
		inline const static void DrawPixel(const Fern::Vector3D& screenPoint,const Fern::Color& color, Fern::Window* window, Fern::DepthBuff* depthBuff) {
			if ((!window) || (!depthBuff))return;
			if (screenPoint.screenx < 0)return;
			if (screenPoint.screenx > window->Width() + 1)return;
			if (screenPoint.screeny < 0)return;
			if (screenPoint.screeny > window->Height() + 1)return;

			if (screenPoint.screendepth > depthBuff->currentDepthValue[(int)screenPoint.screeny][(int)screenPoint.screenx])return;

			putpixel(screenPoint.screenx, screenPoint.screeny, color.ToEasyXColor());
			depthBuff->currentDepthValue[(int)screenPoint.screeny][(int)screenPoint.screenx] = screenPoint.screendepth;
		}

		inline void DrawPixel(const Fern::Vector3D& screenPoint, const Fern::Color& color) {

			if ((!this->window) || (!this->depthBuff))return;
			if (screenPoint.screenx < 0)return;
			if (screenPoint.screenx > this->window->Width() + 1)return;
			if (screenPoint.screeny < 0)return;
			if (screenPoint.screeny > this->window->Height() + 1)return;

			if (screenPoint.screendepth > this->depthBuff->currentDepthValue[(int)screenPoint.screeny][(int)screenPoint.screenx])return;

			putpixel(screenPoint.screenx, screenPoint.screeny, color.ToEasyXColor());
			this->depthBuff->currentDepthValue[(int)screenPoint.screeny][(int)screenPoint.screenx] = screenPoint.screendepth;
		}

		inline const static void DrawPixel(int x,int y,double depth, const Fern::Color& color, Fern::Window* window, Fern::DepthBuff* depthBuff) {
			if ((!window) || (!depthBuff))return;
			if (x < 0)return;
			if (x > window->Width() + 1)return;
			if (y < 0)return;
			if (y > window->Height() + 1)return;

			if (depth > depthBuff->currentDepthValue[y][x])return;

			putpixel(x,y, color.ToEasyXColor());
			depthBuff->currentDepthValue[y][x] = depth;
		}

		inline void DrawPixel(int x, int y, double depth, const Fern::Color& color) {

			if ((!this->window) || (!this->depthBuff))return;
			if (x < 0)return;
			if (x > this->window->Width() + 1)return;
			if (y < 0)return;
			if (y > this->window->Height() + 1)return;

			if (depth > this->depthBuff->currentDepthValue[y][x])return;

			putpixel(x, y, color.ToEasyXColor());
			this->depthBuff->currentDepthValue[y][x] = depth;
		}

		



		/**
		* @brief 平面叉积判断法函数
		* @deprecated 新版函数实现支持从空间变换结果直接提取Fern::Vector3D对象
		*/
		inline static int crossProduct2D(int Ax, int Ay, int Bx, int By, int Px, int Py) {
		// AB = (Bx - Ax, By - Ay)
		// AP = (Px - Ax, Py - Ay)
		// 叉积 = AB.x * AP.y - AB.y * AP.x
		return (Bx - Ax) * (Py - Ay) - (By - Ay) * (Px - Ax);
		}

		/**
		* @brief 平面叉积判断法函数
		*/
		inline static int crossProduct2D(Vector3D A, Vector3D B, Vector3D P) {
			// AB = (Bx - Ax, By - Ay)
			// AP = (Px - Ax, Py - Ay)
			// 叉积 = AB.x * AP.y - AB.y * AP.x
			return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
		}

		inline static bool pointInTriangle(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Px, int Py) {
			int d1 = crossProduct2D(Ax, Ay, Bx, By, Px, Py);
			int d2 = crossProduct2D(Bx, By, Cx, Cy, Px, Py);
			int d3 = crossProduct2D(Cx, Cy, Ax, Ay, Px, Py);

			bool hasPos = (d1 > 0 || d2 > 0 || d3 > 0);
			bool hasNeg = (d1 < 0 || d2 < 0 || d3 < 0);

			return (!(hasPos && hasNeg));
		}

		/**
		* @brief 绘制填充三角形
		* @warning 该函数或许会在未来遇到性能瓶颈。
		* @deprecated 新版函数实现应当支持从空间变换结果直接提取Fern::Vector3D对象
		* 随着深度缓冲的实现，函数过时。
		*/
		static void drawFillTriangle(Fern::Window * window, Vector3D A, Vector3D B, Vector3D C, Fern::Color color) {
			if (crossProduct2D(A, B, C) > 0)return;

			int xSearchMinRange = A.x, xSearchMaxRange = A.x;
			if (B.x < xSearchMinRange)xSearchMinRange = B.x;
			if (B.x > xSearchMaxRange)xSearchMaxRange = B.x;
			if (C.x < xSearchMinRange)xSearchMinRange = C.x;
			if (C.x > xSearchMaxRange)xSearchMaxRange = C.x;

			int ySearchMinRange = A.y, ySearchMaxRange = A.y;
			if (B.y < ySearchMinRange)ySearchMinRange = B.y;
			if (B.y > ySearchMaxRange)ySearchMaxRange = B.y;
			if (C.y < ySearchMinRange)ySearchMinRange = C.y;
			if (C.y > ySearchMaxRange)ySearchMaxRange = C.y;

			for (int cursorX = xSearchMinRange;cursorX <= xSearchMaxRange;cursorX++) {
				for (int cursorY = ySearchMinRange;cursorY <= ySearchMaxRange;cursorY++) {
					if (pointInTriangle(A.x, A.y, B.x, B.y, C.x, C.y, cursorX, cursorY)) {
	
					}
				}
			}
		}

		/**
		* @brief 绘制填充三角形
		* @warning 该函数或许会在未来遇到性能瓶颈。
		* @deprecated 新版函数实现应当支持从空间变换结果直接提取Fern::Vector3D对象
		* 随着深度缓冲的实现，函数过时。
		*/
		static void drawFillTriangle(int Ax, int Ay, int Bx, int By, int Cx, int Cy, Fern::Color color,Fern::Window* window,Fern::DepthBuff* depthBuff) {
			if (crossProduct2D(Ax, Ay, Bx, By, Cx, Cy) > 0)return;

			int xSearchMinRange = Ax, xSearchMaxRange = Ax;
			if (Bx < xSearchMinRange)xSearchMinRange = Bx;
			if (Bx > xSearchMaxRange)xSearchMaxRange = Bx;
			if (Cx < xSearchMinRange)xSearchMinRange = Cx;
			if (Cx > xSearchMaxRange)xSearchMaxRange = Cx;

			int ySearchMinRange = Ay, ySearchMaxRange = Ay;
			if (By < ySearchMinRange)ySearchMinRange = By;
			if (By > ySearchMaxRange)ySearchMaxRange = By;
			if (Cy < ySearchMinRange)ySearchMinRange = Cy;
			if (Cy > ySearchMaxRange)ySearchMaxRange = Cy;

			for (int cursorX = xSearchMinRange;cursorX <= xSearchMaxRange;cursorX++) {
				for (int cursorY = ySearchMinRange;cursorY <= ySearchMaxRange;cursorY++) {
					if (pointInTriangle(Ax, Ay, Bx, By, Cx, Cy, cursorX, cursorY)) {
			
					}
				}
			}
		}

		

		static void drawLine3D(Window * window, const Vector3D & start, const Vector3D & end, const Color & color) {

		}

		
	};
}