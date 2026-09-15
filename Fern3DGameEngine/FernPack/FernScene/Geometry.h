/**
 * @file Fern3DEngine/FernMath/Geometry.h
 *
 * @brief 基础几何体基类以及一些标准几何体
 * @details
 * 该模块执行基本几何体相关操作
 * 
 * @future
 * 添加模型矩阵存储位置。
 *
 * @author 半人马座beta星
 * @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
 * @date 2026/7/24
 */
#pragma once




namespace Fern::Geo {
	/**
	* @brief 棱结构体
	* 
	*/
	struct Edge {
		union {
			struct {
				int verticeStart;		///<起始点
				int verticeEnd;			///<终止点
			};
			int vertices[2];			///<数组形式的属性
		};
		Color color;

		Edge(int start, int end, Color c) :verticeStart(start), verticeEnd(end), color(c) {}
	};

	/**
	* @brief 面结构体
	*
	*/
	struct Surface {
		union {
			struct {
				int verticeA;			///<顶点A
				int verticeB;			///<顶点B
				int verticeC;			///<顶点C
			};
			int vertices[3];			///<数组形式的属性
		};
		Vector3D normal;				///<法向量
		Color color;

		Surface(int A, int B, int C, Color c) :verticeA(A), verticeB(B), verticeC(C), color(c) {}
	};


	class Geometric {
	public:
		std::vector<Vector3D> verticies;
		//std::vector<std::pair<int, int>> edges;
		std::vector<Edge> edges;
		std::vector<Surface> surfaces;

	public:
		Geometric() {}

		/**
		* @brief 将顶点按照矩阵变换。顶点系列为属性。
		* @details
		* @param const:Matrix4x4& A 变换矩阵
		* @return std::vector<Vector3D> 变换后点列
		* @deprecated 方法实现为测试用。正式实现参考
		* @see std::vector<Vector3D> operator*(const Matrix4x4& A)
		*/
		std::vector<Vector3D> applyMatrixTransform(const Matrix4x4& A) const {
			std::vector<Vector3D> result;
			result.reserve(verticies.size());
			std::ostringstream oss;

			/*
			oss << "传入矩阵\n" << A.values[0][0] << " " << A.values[0][1] << " " << A.values[0][2] << " " << A.values[0][3] << " \n"
				<< A.values[1][0] << " " << A.values[1][1] << " " << A.values[1][2] << " " << A.values[1][3] << " \n"
				<< A.values[2][0] << " " << A.values[2][1] << " " << A.values[2][2] << " " << A.values[2][3] << " \n"
				<< A.values[3][0] << " " << A.values[3][1] << " " << A.values[3][2] << " " << A.values[3][3] << " \n";
			LOG_FATAL(oss.str());
			*/

			
			for (const auto& v : verticies) {
				std::ostringstream oss1, oss2;
				oss1 << "变换点： (" << v.x << "," << v.y << "," << v.z << ") ";
				LOG_WARN(oss1.str());
				Vector3D transformed = A.applyToVector(v);
				result.push_back(A.applyToVector(v)); // 或 A * v
				oss2 << "变换后的点： (" << transformed.x << "," << transformed.y << "," << transformed.z << ") ";
				LOG_WARN(oss2.str());
			}
			return result;
		}
		
		std::vector<Vector3D> operator*(const Matrix4x4& A) const {
			std::vector<Vector3D> result;
			result.reserve(verticies.size());
			for (const auto& v : verticies) {
				result.push_back( A * v);
			}
			return result;
		}
	};

	class Axis :public Geometric {
	public:
		Axis() {
			verticies = {
				Vector3D(0,0,0),
				Vector3D(1,0,0),
				Vector3D(0,1,0),
				Vector3D(0,0,1)
			};
			edges = {
				{0,1,Fern::Color::Red()},
				{0,2,Fern::Color::Green()},
				{0,3,Fern::Color::Blue()}
			};
			surfaces = {};
		}

	};

	class Triangle :public Geometric {
	public:
		Triangle() {
			verticies = {
				Vector3D(1,2,3),
				Vector3D(4,5,6),
				Vector3D(7,8,9)
			};
			edges = {
			};
			surfaces = {
				{0,1,2,Fern::Color::RimuluBlue()}
			};
		}

	};

	class standardCube :public Geometric {
	public:
		standardCube() {
			verticies = {
				Vector3D(0,0,0),
				Vector3D(1,0,0),
				Vector3D(1,1,0),
				Vector3D(0,1,0),
				Vector3D(0,0,1),
				Vector3D(1,0,1),
				Vector3D(1,1,1),
				Vector3D(0,1,1)
			};
			edges = {
				{0,1,Fern::Color::Red()},
				{1,2,Fern::Color::Cyan()},
				{2,3,Fern::Color::Cyan()},
				{3,0,Fern::Color::Green()},
				{4,5,Fern::Color::Cyan()},
				{5,6,Fern::Color::Cyan()},
				{6,7,Fern::Color::Cyan()},
				{7,4,Fern::Color::Cyan()},
				{0,4,Fern::Color::Blue()},
				{1,5,Fern::Color::Cyan()},
				{2,6,Fern::Color::Cyan()},
				{3,7,Fern::Color::Cyan()}
			};
			surfaces = {
				{0,2,1,Fern::Color::RimuluBlue()},{0,3,2,Fern::Color::RimuluBlue()},
				{0,7,3,Fern::Color::White()},{0,4,7,Fern::Color::White()},
				{0,5,4,Fern::Color::White()},{0,1,5,Fern::Color::White()},
				{6,7,4,Fern::Color::White()},{6,4,5,Fern::Color::White()},
				{6,5,1,Fern::Color::White()},{6,1,2,Fern::Color::White()},
				{6,2,3,Fern::Color::White()},{6,3,7,Fern::Color::White()}
			};
		}
	};

	class standardCube2 :public Geometric {
	public:
		standardCube2() {
			verticies = {
				Vector3D(-1,-1,-1),
				Vector3D(1,-1,-1),
				Vector3D(1,1,-1),
				Vector3D(-1,1,-1),
				Vector3D(-1,-1,1),
				Vector3D(1,-1,1),
				Vector3D(1,1,1),
				Vector3D(-1,1,1)
			};
			edges = {
				{0,1,Fern::Color::Red()},
				{1,2,Fern::Color::Cyan()},
				{2,3,Fern::Color::Cyan()},
				{3,0,Fern::Color::Green()},
				{4,5,Fern::Color::Cyan()},
				{5,6,Fern::Color::Cyan()},
				{6,7,Fern::Color::Cyan()},
				{7,4,Fern::Color::Cyan()},
				{0,4,Fern::Color::Blue()},
				{1,5,Fern::Color::Cyan()},
				{2,6,Fern::Color::Cyan()},
				{3,7,Fern::Color::Cyan()}
			};
			surfaces = {
				{0,2,1,Fern::Color::RimuluBlue()},
				{0,3,2,Fern::Color::RimuluBlue()},
				{0,7,3,Fern::Color::Red()},
				{0,4,7,Fern::Color::Red()},
				{0,5,4,Fern::Color::White()},
				{0,1,5,Fern::Color::White()},
				{6,7,4,Fern::Color::Green()},
				{6,4,5,Fern::Color::Green()},
				{6,5,1,Fern::Color::Orange()},
				{6,1,2,Fern::Color::Orange()},
				{6,2,3,Fern::Color::Yellow()},
				{6,3,7,Fern::Color::Yellow()}
			};
		}
	};
}