/**
* @brief 程序头文件统一入口。在此处管理包关系。
*/

#pragma once


/// 引擎名称源于《葬送的芙莉莲》中的角色菲伦（ [德]Fern, 意为遥远的 ）。
/// 我说她是十七岁的妈妈有没有懂的（（（
namespace Fern{}

#define Camera_Near_Plane  0.1
#define Ndc_Near_Plane 0

///< std dependency || 标准库依赖		||依赖文件
#include <iostream>						
#include <vector>
#include <fstream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <filesystem>
#ifdef _WIN32
	#include <Windows.h>
#endif
#include <easyx.h>
#include <cstdint>

///< basic function || 基本功能		||文件编号		||模块功能
/*
	FernPack/FernBasicFunction/
													或许我需要一个文件方便高效地处理字符串
		LogBuff.h					0				异步日志
		Color.h						1				颜色定义
		
*/
#include "FernPack/FernBasicFunction/LogBuff.h"
#include "FernPack/FernBasicFunction/Color.h"

///< math library || 数学运算库		||文件编号		||模块功能
/*
	FernPack/FernMath/
		MathUtils.h									进行最基本的数学运算
		Vector3D.h									进行向量计算
		Matrix4x4.h									进行矩阵运算
		Quaternion.h								四元数计算（未实装，需先搞懂数学原理）
*/
#include "FernPack/FernMath/MathUtils.h"
#include "FernPack/FernMath/Vector3D.h"
#include "FernPack/FernMath/Matrix4x4.h"
#include "FernPack/FernMath/Quaternion.h"

///< core system || 核心系统		||文件编号		||模块功能
/*
	FernPack/FernCore/
		Window.h									视窗管理
		Timer.h										时间管理（未实装）
		Input.h										输入管理与响应（未实装）
*/
#include "FernPack/FernCore/Window.h"
#include "FernPack/FernCore/Timer.h"
#include "FernPack/FernCore/Input.h"

///< scene manage || 场景管理		||文件编号		||模块功能
/*
	FernPack/FernScene/
		Geometry.h									场景中几何体的定义
		Camera.h									场景中相机的定义
													场景中区块的定义（待后续添加）（一个区块中可以有很多个几何体和相机）
													整个场景对象的定义（待后续添加）（一个场景对象可以有多个区块，渲染时按视距取出区块渲染即可）
													地图定义（待后续添加）（一个地图可以有很多个场景）
*/
#include "FernPack/FernScene/Geometry.h"
#include "FernPack/FernScene/Camera.h"

///< animation || 动画模块			||文件编号		||模块功能
/*
													(待后续添加）
*/

///< render machine || 渲染管线		||文件编号		||模块功能
/*
	FernPack/FernRender/
		DepthBuff.h									深度缓冲
		Render.h									渲染函数
		LineRender.h								线段渲染函数（测试功能，测试完成后应当将可用功能合并到Render中并移除该文件）
		MessageBox.h								屏幕2D渲染信息框（后续应当设立Render2D.h文件，以渲染不同类别的2d悬浮消息）
		RenderCommand.h								渲染命令（用于向渲染线程传递命令）
		RenderCommandQueue.h						渲染命令队列（先入先出）缓冲
		RenderThread.h								渲染线程（待后续添加）（渲染压力不应该由主线程分担，主线程应该充当指挥）
*/
#include "FernPack/FernRender/DepthBuff.h"
#include "FernPack/FernRender/Render.h"
//#include "FernPack/FernRender/LineRender.h"
#include "FernPack/FernRender/MessageBox.h"
#include "FernPack/FernRender/RenderCommand.h"
#include "FernPack/FernRender/RenderCommandQueue.h"
#include "FernPack/FernRender/RenderThread.h"

///< activity || 活动页面			||文件编号		||模块功能
/*
													(待后续添加）
*/