/**
* @file Fern3DEngine / FernRender / RenderCommand.h
*
*@brief 渲染线程
* @details
* 该模块接受渲染命令并将渲染命令绘制到画布上。
*

*
*@author 半人马座beta星
* @copyright Copyright(c) 2026 Rimuru Central Institute of Computer Science.All rights reserved.
* @date 2026 / 8 / 4
*/

#pragma once

namespace Fern {
	static void fastDrawFillTriangle(Vector3D& A, Vector3D& B, Vector3D& C, const Fern::Color& color, Fern::Window* window, Fern::DepthBuff* depthBuff) {

		Fern::Vector3D* pSorted[3] = { &A, &B, &C };

		// 按 y 排序，y 最小的在 pSorted[0]
		if (pSorted[0]->y > pSorted[1]->y) { Fern::Vector3D* t = pSorted[0]; pSorted[0] = pSorted[1]; pSorted[1] = t; }
		if (pSorted[0]->y > pSorted[2]->y) { Fern::Vector3D* t = pSorted[0]; pSorted[0] = pSorted[2]; pSorted[2] = t; }
		if (pSorted[1]->y > pSorted[2]->y) { Fern::Vector3D* t = pSorted[1]; pSorted[1] = pSorted[2]; pSorted[2] = t; }

		// 如果 y 都相同，三角形退化为一条线或点，直接返回
		if (pSorted[0]->y == pSorted[2]->y) {
			return;
		}

		// 如果有两个 y 相同，他们需要按x排序
		if ((pSorted[0]->y == pSorted[1]->y) && (pSorted[0]->x > pSorted[1]->x)) { Fern::Vector3D* t = pSorted[0]; pSorted[0] = pSorted[1]; pSorted[1] = t; }
		if ((pSorted[1]->y == pSorted[2]->y) && (pSorted[1]->x > pSorted[2]->x)) { Fern::Vector3D* t = pSorted[1]; pSorted[1] = pSorted[2]; pSorted[2] = t; }


		// 确定左右边界
		Fern::Vector3D* pLeftStart = pSorted[0];
		Fern::Vector3D* pRightStart = pSorted[0];
		Fern::Vector3D* pLeftEnd = pSorted[1];
		Fern::Vector3D* pRightEnd = pSorted[2];

		if (pSorted[0]->y == pSorted[1]->y) {
			pRightStart = pSorted[1];
			pLeftEnd = pSorted[2];
		}
		if (pSorted[1]->y == pSorted[2]->y) {
			pLeftEnd = pSorted[2];
			pRightEnd = pSorted[1];
		}

		//规整操作


		int xLeft, xRight;

		for (int y = (int)pSorted[0]->y; y <= (int)pSorted[2]->y; y++) {
			//判断该行是否应该被丢弃，如果应该，那么不执行该循环
			if (y < 0)continue;
			if (y >= window->height)continue;


			// 边界 x
			xLeft = (int)(Fern::Math::insert((int)pLeftStart->x, (int)pLeftEnd->x, Fern::Math::getInsertNumber((int)pLeftStart->y, (int)pLeftEnd->y, y)) - 0.5);
			xRight = (int)(Fern::Math::insert((int)pRightStart->x, (int)pRightEnd->x, Fern::Math::getInsertNumber((int)pRightStart->y, (int)pRightEnd->y, y)) + 0.5);

			//计算左右边界的深度值
			double depthLeft = Fern::Math::insert(pLeftStart->z, pLeftEnd->z, Fern::Math::getInsertNumber((int)pLeftStart->y, (int)pLeftEnd->y, y));
			double depthRight = Fern::Math::insert(pRightStart->z, pRightEnd->z, Fern::Math::getInsertNumber((int)pRightStart->y, (int)pRightEnd->y, y));

			if (xLeft > xRight) {
				{ int  t = xLeft; xLeft = xRight;xRight = t; }
				{ double t = depthLeft;depthLeft = depthRight;depthRight = t; }
			}

			// 绘制该行未被丢弃的部分

			for (int x = xLeft; x <= xRight; ++x) {
				if (x < 0)continue;
				if (x >= window->width)continue;

				float currentDepth = Fern::Math::insert(depthLeft, depthRight, Fern::Math::getInsertNumber(xLeft, xRight, x));

				Render::DrawPixel(x, y, currentDepth, color, window, depthBuff);
			}



			// 边界切换（修复后）
			if (y == (int)pLeftEnd->y && y == (int)pRightEnd->y) {
				// 同时到达底部，直接结束
				break;
			}
			else if (y == (int)pLeftEnd->y) {
				pLeftStart = pLeftEnd;
				pLeftEnd = pRightEnd;
			}
			else if (y == (int)pRightEnd->y) {
				pRightStart = pRightEnd;
				pRightEnd = pLeftEnd;
			}


		}
	}
}

namespace Fern::RenderCommandManip {
	static void Control_Clear(Fern::RenderCommand::Command cmd, Fern::Window* window, Fern::DepthBuff* depthBuff){}
	static void Control_Present(Fern::RenderCommand::Command cmd, Fern::Window* window, Fern::DepthBuff* depthBuff) {}
	static void Draw_Triangle(Fern::RenderCommand::Command cmd, Fern::Window* window, Fern::DepthBuff* depthBuff) {
		//首先判断三角形全留全弃
		bool A_in = cmd.screenPointA.screendepth >= Ndc_Near_Plane;
		bool B_in = cmd.screenPointB.screendepth >= Ndc_Near_Plane;
		bool C_in = cmd.screenPointC.screendepth >= Ndc_Near_Plane;

		if (A_in && B_in && C_in) {
			fastDrawFillTriangle(cmd.screenPointA, cmd.screenPointB, cmd.screenPointC, cmd.color, window, depthBuff);
		}
		if (!A_in && !B_in && !C_in)return;

		Fern::Vector3D *P1, *P2, *P3;
		Fern::Vector3D P4, P5;

		//找出与其他两点位于屏幕两侧的点，记为P3
		if (A_in == B_in) {
			P1 = &cmd.screenPointA;
			P2 = &cmd.screenPointB;
			P3 = &cmd.screenPointC;
		}
		else if (B_in == C_in) {
			P1 = &cmd.screenPointB;
			P2 = &cmd.screenPointC;
			P3 = &cmd.screenPointA;
		}
		else {
			P1 = &cmd.screenPointC;
			P2 = &cmd.screenPointA;
			P3 = &cmd.screenPointB;
		}

		P4.z = Ndc_Near_Plane;
		P4.x = Fern::Math::insert(P3->x, P1->x, Fern::Math::getInsertNumber(P3->z, P1->z, Ndc_Near_Plane));
		P4.y = Fern::Math::insert(P3->y, P1->y, Fern::Math::getInsertNumber(P3->z, P1->z, Ndc_Near_Plane));

		P5.z = Ndc_Near_Plane;
		P5.x = Fern::Math::insert(P3->x, P2->x, Fern::Math::getInsertNumber(P3->z, P2->z, Ndc_Near_Plane));
		P5.y = Fern::Math::insert(P3->y, P2->y, Fern::Math::getInsertNumber(P3->z, P2->z, Ndc_Near_Plane));


		/*
		if (P3->z > Ndc_Near_Plane) {
			fastDrawFillTriangle(*P3, P4, P5, cmd.color, window, depthBuff);
		}
		else {
			fastDrawFillTriangle(*P1, *P2, P5, cmd.color, window, depthBuff);
			fastDrawFillTriangle(P4, *P1, P5, cmd.color, window, depthBuff);
		}
		*/
		fastDrawFillTriangle(P4, *P1, P5, cmd.color, window, depthBuff);


	}
	static void Draw_Line(Fern::RenderCommand::Command cmd, Fern::Window* window, Fern::DepthBuff* depthBuff) {}
}

namespace Fern::RenderThread {
	int main(Fern::RenderCommand::Queue& queue, Fern::Window *window, Fern::DepthBuff *depthBuff) {
        while (true) {
            RenderCommand::Command cmd;
            if (!queue.Pop(cmd)) break;  // 队列停止且为空

            switch (cmd.type) {
            case RenderCommand::Type::Control_Clear:
                window->Clear();
                depthBuff->Reset();
                break;

            case RenderCommand::Type::Control_Present:
                window->Present();
                break;

            case RenderCommand::Type::Draw_Triangle:
				//Fern::RenderCommandManip::Draw_Triangle(cmd, window, depthBuff);
				fastDrawFillTriangle(cmd.screenPointA, cmd.screenPointB, cmd.screenPointC, cmd.color, window, depthBuff);
                break;

            case RenderCommand::Type::Draw_Line:
                // 绘制直线命令
                break;

            default:
                // 未知命令，忽略或记录日志
                break;
            }
        }
        return 0;
	}
}