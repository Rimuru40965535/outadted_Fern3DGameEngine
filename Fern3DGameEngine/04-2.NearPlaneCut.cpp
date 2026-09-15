#include "Fern3DGameEngine.h"

int main() {
	LOG_INSTANCE.start("04-2.NearPlaneCut.log");
	LOG_INFO("程序开始运行");


	int screenWid = 1200;
	int screenHei = 900;

	Fern::Window window(screenWid, screenHei, "04.Rotating Cube", !EX_SHOWCONSOLE);

	Fern::Camera camera(
		Fern::Vector3D(0, 0, -1.00), 
		Fern::Vector3D(0, 0, 1),
		Fern::Vector3D(0, 1, 0), 
		Fern::Math::PI * 2 / 3, 1.0 * screenWid / screenHei, 0.1, 100.0);

	Fern::DepthBuff depthBuff(screenWid, screenHei);

	Fern::Render render(&window, &camera, &depthBuff);

	Fern::Geo::standardCube2 cube1, cube2, cube3, cube4, cube5;
	Fern::Geo::Triangle T1;

	Fern::Matrix4x4 cube1ModelMatrix, cube2ModelMatrix, cube3ModelMatrix, cube4ModelMatrix, cube5ModelMatrix, mvp;

	mvp = camera.viewMatrix * camera.projMatrix * window.windowMatrix;

	std::vector<Fern::Vector3D> cube1RenderDots, cube2RenderDots, cube3RenderDots, cube4RenderDots, cube5RenderDots;

	Fern::Matrix4x4 T1ModelMatrix;
	std::vector<Fern::Vector3D> T1RenderDots;

	Fern::RenderCommand::Queue cmdQueue;

	std::thread renderThread(Fern::RenderThread::main,
		std::ref(cmdQueue),
		&window,
		&depthBuff);

	while (!window.ShouldClose()) {

		cube1ModelMatrix = Fern::Matrix4x4::Translation(Fern::Vector3D(0, 0, 0));

		cube1RenderDots = cube1 * (cube1ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);

		for (const auto& _ : cube1.surfaces) {
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube1RenderDots[_.verticeA];
			triCmd.screenPointB = cube1RenderDots[_.verticeB];
			triCmd.screenPointC = cube1RenderDots[_.verticeC];
			triCmd.color = _.color;
			cmdQueue.Push(triCmd);
		}

		Fern::RenderCommand::Command present(Fern::RenderCommand::Control_Present);
		cmdQueue.Push(present);

	}




	LOG_INFO("程序停止运行");
	LOG_INSTANCE.stop();
	return 0;
}