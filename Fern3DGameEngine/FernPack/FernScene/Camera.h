/**
 * @file Fern3DEngine/FernCore/Camera.h
 *
 * @brief 相机模块
 * @details
 * 该模块管理相机对象
 *
 *
 * @author 半人马座beta星
 * @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
 * @date 2026/7/22
 */
#pragma once



namespace Fern {
	class Camera {
	public:
		Matrix4x4 viewMatrix;	///<形位矩阵    世界空间坐标系->相机空间坐标系
		Matrix4x4 projMatrix;	///<透视矩阵    相机空间坐标系->NDC归一化坐标系

		double fov;				///<视场广角
		double aspectRatio;		///<宽高比
		double nearPlane;		///<近裁平面
		double farPlane;		///<远裁平面
	public:
		Camera(Vector3D cameraPosition , Vector3D cameraLookAt, Vector3D cameraUp, double fov = Fern::Math::PI * 2 / 3, double asp = 800 / 600, double nPl = 0.1, double fPl = 100.0)
			:viewMatrix(MATRIX_INIT_WITH_ALL_0), fov(fov),aspectRatio(asp),nearPlane(nPl), farPlane(fPl){
			// 1. 计算坐标轴
			Vector3D forward = (cameraLookAt - cameraPosition).makeLengthUnitCopy(); 
			Vector3D right = (cameraUp % forward).makeLengthUnitCopy();
			Vector3D upCorrect = (forward % right).makeLengthUnitCopy(); // 重新正交化

			// 2. 构建 LookAt 矩阵 (列主序存储，但你的 Matrix4x4 是行主序，所以需要转置)
		    //    标准 LookAt 矩阵 (行主序) 为:
		    //    [ right.x, right.y, right.z, -dot(right, cameraPosition) ]
		    //    [ up.x,   up.y,   up.z,   -dot(up, cameraPosition)    ]
		    //    [ -forward.x, -forward.y, -forward.z, dot(forward, cameraPosition) ]
		    //    [ 0,       0,       0,       1                  ]
			//viewMatrix = Matrix4x4::Identity();

			viewMatrix.values[0][0] = right.x;
			viewMatrix.values[0][1] = right.y;
			viewMatrix.values[0][2] = right.z;
			viewMatrix.values[0][3] = -(right.x * cameraPosition.x + right.y * cameraPosition.y + right.z * cameraPosition.z);

			viewMatrix.values[1][0] = upCorrect.x;
			viewMatrix.values[1][1] = upCorrect.y;
			viewMatrix.values[1][2] = upCorrect.z;
			viewMatrix.values[1][3] = -(upCorrect.x * cameraPosition.x + upCorrect.y * cameraPosition.y + upCorrect.z * cameraPosition.z);

			viewMatrix.values[2][0] = -forward.x;
			viewMatrix.values[2][1] = -forward.y;
			viewMatrix.values[2][2] = -forward.z;
			viewMatrix.values[2][3] = (forward.x * cameraPosition.x + forward.y * cameraPosition.y + forward.z * cameraPosition.z);

			viewMatrix.values[3][0] = 0.0;
			viewMatrix.values[3][1] = 0.0;
			viewMatrix.values[3][2] = 0.0;
			viewMatrix.values[3][3] = 1.0;

			this->projMatrix = setPerspectMatrix();

		}
		
		
		/**
		* @brief 透视投影矩阵
		* @return Matrix4x4 相机坐标系变换为NDC空间坐标系
		*
		*/
		Matrix4x4 setPerspectMatrix() {
			double tanHalfFov = Fern::Math::Tangent(this->fov / 2.0);
			Matrix4x4 result;
			result.values[0][0] = 1.0 / (this->aspectRatio * tanHalfFov);
			result.values[1][1] = 1.0 / tanHalfFov;
			result.values[2][2] = -(this->farPlane + this->nearPlane) / (this->farPlane - this->nearPlane);
			result.values[2][3] = -(2.0 * this->farPlane * this->nearPlane) / (this->farPlane - this->nearPlane);
			result.values[3][2] = -1.0;
			result.values[3][3] = 0.0;
			return result;
		}
	};
}