/**
* @brief 深度缓冲模块
* @details
* 
* @author 半人马座beta星
* @copyright Copyright (c) 2026 Rimuru Central Institute of Computer Science. All rights reserved.
* @date 2026/7/26
* 
*/
#pragma once

#define depthAt(x,y) currentDepthValue[y][x]

namespace Fern {
	class DepthBuff {
	public:
		double** currentDepthValue;
		int screenWidth;
		int screenHeigth;

	public:
		DepthBuff(int scrWid = 800, int scrHei = 600) :screenWidth(scrWid), screenHeigth(scrHei) {
			currentDepthValue = new double* [scrHei];
			for (int y = 0;y < scrHei; y++) {
				currentDepthValue[y] = new double [scrWid] ;
				for (int x = 0; x < scrWid;x++) {
					currentDepthValue[y][x] = 1.0f;
				}
			}
		}

		

		void Reset(float baseValue = 1.0) {
			for (int currentRow = 0;currentRow < this->screenHeigth; currentRow++) {
				for (int currentColumn = 0; currentColumn < this->screenWidth;currentColumn++) {
					currentDepthValue[currentRow][currentColumn] = baseValue;
				}
			}
		}



	};
}