/**
 * @file Fern3DEngine/FernRender/RenderCommand.h
 *
 * @brief 渲染命令
 * @details
 * 该模块执行其它业务想渲染线程的调用，并且给予统一的渲染接口
 *

 *
 * @author 半人马座beta星
 * @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
 * @date 2026/8/4
 */
#pragma once

namespace Fern::RenderCommand {
	enum Type {
		TheradJoin = 0,
		Control_Clear,
		Control_Present,

		Draw_Line = 0x10,

		Draw_Triangle = 0x20,
		Draw_Triangle_With_Light_Flection,
		Draw_Triangle_With_Texture,
		Draw_Triangle_With_Light_Flection_And_Texture,

		Draw_Float_MessageBox = 0x30,
		Draw_Float_MessageBox_At_Certain_Point_Towards_Me,
		Draw_Float_MessageBox_At_Cursor,

		Draw_UI_Blank = 0x40,
		Draw_UI_Text,
		Draw_UI_Button
	};

	struct Command {
		Type type;
		union {
			struct
			{
				Vector3D screenPointA;
				Vector3D screenPointB;
				Vector3D screenPointC;
			};
			Vector3D screenPoint[3];
		};
		Color color;

		Command() {}
		Command(Type t):type(t){}
		Command(const Command& A) {
			this->type = A.type;
			this->screenPointA = A.screenPointA;
			this->screenPointB = A.screenPointB;
			this->screenPointC = A.screenPointC;
			this->color = A.color;
		}

		Command& operator=(const Command& A) {
			this->type = A.type;
			this->screenPointA = A.screenPointA;
			this->screenPointB = A.screenPointB;
			this->screenPointC = A.screenPointC;
			this->color = A.color;
			return *this;
		}

	};

}