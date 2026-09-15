/**
* @brief 消息框
* 
* @details
* 调试功能。
* 在场景绘制完成以后，绘制消息框。
* 
* 
* 
*/

#pragma once



//layouts||排版宏定义
#define LAYOUT_HORIZONTAL_LEFT 0x00000004
#define LAYOUT_HORIZONTAL_RIGHT 0x00000001
#define LAYOUT_HORIZONTAL_CENTER 0x00000002

#define LAYOUT_VERTICAL_LEFT 0x00000040
#define LAYOUT_VERTICAL_RIGHT 0x00000010
#define LAYOUT_VERTICAL_CENTER 0x00000020

namespace Fern::Debug {
	class FloatMessage {
	public:
		Fern::Color backgroundColor;
		Fern::Color textColor;
		

	public:
		FloatMessage() :backgroundColor(Fern::Color::RimuluBlue()), textColor(Fern::Color::Black()) {}
		

	};
}