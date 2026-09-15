#include "Fern3DGameEngine.h"

int main() {

	LOG_INSTANCE.start("04.RotatingCube.log");
	LOG_INFO("程序开始运行");

	int screenWid = 1200;
	int screenHei = 900;

	Fern::Window window(screenWid, screenHei, "04.Rotating Cube", !EX_SHOWCONSOLE);
	Fern::Camera camera(Fern::Vector3D(1.5, 1.5, 1.5), Fern::Vector3D(0, 0, 0), Fern::Vector3D(0, 1, 0), Fern::Math::PI * 2/3, 1.0*screenWid/screenHei, 0.1, 100.0);
	Fern::DepthBuff depthBuff(screenWid, screenHei);

	Fern::Render render(&window, &camera, &depthBuff);

	Fern::Geo::standardCube2 cube1,cube2,cube3,cube4,cube5;
	Fern::Geo::Triangle T1;

	Fern::Matrix4x4 cube1ModelMatrix,cube2ModelMatrix, cube3ModelMatrix, cube4ModelMatrix, cube5ModelMatrix,mvp;

	mvp = camera.viewMatrix * camera.projMatrix * window.windowMatrix;

	std::vector<Fern::Vector3D> cube1RenderDots, cube2RenderDots,cube3RenderDots, cube4RenderDots, cube5RenderDots;

	Fern::Matrix4x4 T1ModelMatrix;
	std::vector<Fern::Vector3D> T1RenderDots;

	Fern::RenderCommand::Queue cmdQueue;
	std::thread renderThread(Fern::RenderThread::main,
		std::ref(cmdQueue),
		&window,
		&depthBuff);

	double angularSpeed = 0.0;
	//double angularSpeed = Fern::Math::PI* 2/3;

	while (!window.ShouldClose()) {
		cmdQueue.Push(Fern::RenderCommand::Command(Fern::RenderCommand::Control_Clear));


		window.PollEvents();


		cube1ModelMatrix =  Fern::Matrix4x4::RotationX(angularSpeed);
		
		
		cube2ModelMatrix = Fern::Matrix4x4::Translation(Fern::Vector3D(0, 0, -3))
			* Fern::Matrix4x4::RotationAroundOriginX(angularSpeed, Fern::Vector3D(0, 0, -3))
			* Fern::Matrix4x4::RotationAroundOriginY(angularSpeed * 2 / 3, Fern::Vector3D(0, 0, -3));
		cube3ModelMatrix = Fern::Matrix4x4::Translation(Fern::Vector3D(0, -3, 0))
			* Fern::Matrix4x4::RotationAroundOriginY(angularSpeed, Fern::Vector3D(0, -3, 0))
			* Fern::Matrix4x4::RotationAroundOriginZ(angularSpeed * 2 / 3, Fern::Vector3D(0, -3, 0));
		cube4ModelMatrix = Fern::Matrix4x4::Translation(Fern::Vector3D(-3, 0, 0))
			* Fern::Matrix4x4::RotationAroundOriginZ(angularSpeed, Fern::Vector3D(-3, 0, 0))
			* Fern::Matrix4x4::RotationAroundOriginX(angularSpeed * 2 / 3, Fern::Vector3D(-3, 0, 0));
		cube5ModelMatrix = Fern::Matrix4x4::Translation(Fern::Vector3D(-3, 0, 0))
			* Fern::Matrix4x4::RotationZ(angularSpeed);
		//cube5ModelMatrix = Fern::Matrix4x4::Translation(angularSpeed * Fern::Vector3D(1, 1, 1));
		T1ModelMatrix = Fern::Matrix4x4::RotationX(angularSpeed);
		

		cube1RenderDots = cube1 * (cube1ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);
		cube2RenderDots = cube2 * (cube2ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);
		cube3RenderDots = cube3 * (cube3ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);
		cube4RenderDots = cube4 * (cube4ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);
		cube5RenderDots = cube5 * (cube5ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);

		T1RenderDots = T1 * (T1ModelMatrix * camera.viewMatrix * camera.projMatrix * window.windowMatrix);

		for (const auto& _ : cube1.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube1RenderDots[_.verticeA], 
				cube1RenderDots[_.verticeB], 
				cube1RenderDots[_.verticeC],
				_.color,&window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube1RenderDots[_.verticeA];
			triCmd.screenPointB = cube1RenderDots[_.verticeB];
			triCmd.screenPointC = cube1RenderDots[_.verticeC];
			triCmd.color = _.color;
			cmdQueue.Push(triCmd);
		}

		
		for (const auto& _ : cube2.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube2RenderDots[_.verticeA], 
				cube2RenderDots[_.verticeB],
				cube2RenderDots[_.verticeC],
				_.color, &window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube2RenderDots[_.verticeA];
			triCmd.screenPointB = cube2RenderDots[_.verticeB];
			triCmd.screenPointC = cube2RenderDots[_.verticeC];
			triCmd.color = _.color;
			cmdQueue.Push(triCmd);
		}

		for (const auto& _ : cube3.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube3RenderDots[_.verticeA],
				cube3RenderDots[_.verticeB],
				cube3RenderDots[_.verticeC],
				_.color, &window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube3RenderDots[_.verticeA];
			triCmd.screenPointB = cube3RenderDots[_.verticeB];
			triCmd.screenPointC = cube3RenderDots[_.verticeC];
			triCmd.color = _.color;
			//cmdQueue.Push(triCmd);
		}


		for (const auto& _ : cube4.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube4RenderDots[_.verticeA],
				cube4RenderDots[_.verticeB],
				cube4RenderDots[_.verticeC],
				_.color, &window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube4RenderDots[_.verticeA];
			triCmd.screenPointB = cube4RenderDots[_.verticeB];
			triCmd.screenPointC = cube4RenderDots[_.verticeC];
			triCmd.color = _.color;
			//cmdQueue.Push(triCmd);
		}

		for (const auto& _ : cube5.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube4RenderDots[_.verticeA],
				cube4RenderDots[_.verticeB],
				cube4RenderDots[_.verticeC],
				_.color, &window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = cube5RenderDots[_.verticeA];
			triCmd.screenPointB = cube5RenderDots[_.verticeB];
			triCmd.screenPointC = cube5RenderDots[_.verticeC];
			triCmd.color = _.color;
			//cmdQueue.Push(triCmd);
		}
		
		for (const auto& _ : T1.surfaces) {
			/*
			render.fastDrawFillTriangle(
				cube4RenderDots[_.verticeA], 
				cube4RenderDots[_.verticeB],
				cube4RenderDots[_.verticeC],
				_.color, &window, &depthBuff
			);
			*/
			Fern::RenderCommand::Command triCmd(Fern::RenderCommand::Draw_Triangle);
			triCmd.screenPointA = T1RenderDots[_.verticeA];
			triCmd.screenPointB = T1RenderDots[_.verticeB];
			triCmd.screenPointC = T1RenderDots[_.verticeC];
			triCmd.color = _.color;
			//cmdQueue.Push(triCmd);
		}

		
		Fern::RenderCommand::Command present(Fern::RenderCommand::Control_Present);
		cmdQueue.Push(present);

		angularSpeed += 0.1;
	}


	LOG_INSTANCE.stop();

	return 0;
}