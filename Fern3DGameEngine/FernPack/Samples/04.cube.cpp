#define LOG_BUFF_SETTINGS_CONSOLE_OUTPUT false
#define LOG_BUFF_SETTINGS_MINIMUM_LEVEL Fern::Level::INFO
#include "../FernMath/Vector3D.h"
#include "../FernMath/Matrix4x4.h"
#include "../FernMath/Geometry.h"

#include "../FernCore/Window.h"
#include "../FernCore/Color.h"
#include "../FernCore/Camera.h"

#include "../FernRender/LineRender.h"



#include "../Log/LogBuff.h"

#include <vector>

static Fern::Color colorInsert(Fern::Color color1,Fern::Color color2,double insert) {
    return Fern::Color(
        insert * color2.r + (1 - insert) * color1.r + 0.5,
        insert * color2.g + (1 - insert) * color1.g + 0.5,
        insert * color2.b + (1 - insert) * color1.b + 0.5,
        insert * color2.a + (1 - insert) * color1.a + 0.5
    );
}

void RenderTest() {
    int screenWidth = 1200, screenHeight = 900;
    Fern::Window window(screenWidth, screenHeight, "Rotating Cube", !EX_SHOWCONSOLE,
        Fern::Vector3D(1.5, 1.5, 1.5),
        Fern::Vector3D(0.0, 0.0, 0.0),
        Fern::Vector3D(0.0, 1.0, 0.0),
        Fern::Math::PI * 2 / 3,
        0.1,
        100
    );
    Fern::Vector3D A(0, 0, 0), B(0, 1, 0), C(1, 0, 0);
    Fern::Matrix4x4 finalTransformMatrixAxis = window.cam.viewMatrix * window.cam.projMatrix * window.windowMatrix;
    A = finalTransformMatrixAxis*A;
    B = finalTransformMatrixAxis*B;
    C = finalTransformMatrixAxis*C;

    while (1) {
        window.Clear();
        Fern::LineRender::DrawLine(&window, 100, 100, 500, 500, Fern::Color::White());
        //Fern::LineRender::DrawLine(&window, A.x, A.y, B.x, B.y, Fern::Color::White());
        //Fern::Render::fastDrawFillTriangle(&window, A, B, C, Fern::Color::White());
    }
}

int main() {
	LOG_INSTANCE.start("app.log");
    LOG_ERROR("程序开始运行");
    std::ostringstream oss1, oss2, oss3,oss4,oss5;
    std::wostringstream oss6;
    

	int screenWidth = 1200, screenHeight = 900;
	Fern::Window window(screenWidth, screenHeight, "Rotating Cube", !EX_SHOWCONSOLE, 
        Fern::Vector3D(1.5, 1.5, 1.5),
        Fern::Vector3D(0.0, 0.0, 0.0),
        Fern::Vector3D(0.0, 1.0, 0.0),
        Fern::Math::PI * 2/3,
        0.1,
        100
    );

    //创建几何体
    //Fern::Geo::standardCube cube;
    Fern::Geo::Axis axis;
    Fern::Matrix4x4 finalTransformMatrixAxis;
    
    Fern::Geo::standardCube2 cube;
    Fern::Geo::standardCube2 cube2;

    Fern::Matrix4x4 finalTransformMatrixCube;
    Fern::Matrix4x4 finalTransformMatrixCube2;
    
    //double rotateSpeed = 0;
    double rotateSpeed = 0.01;
    //double rotateSpeed = Fern::Math::PI * 2/4;

    //渲染点列
    std::vector<Fern::Vector3D> axisRenderDots;
    std::vector<Fern::Vector3D> cubeRenderDots;
    std::vector<Fern::Vector3D> cube2RenderDots;
   
    finalTransformMatrixAxis = window.cam.viewMatrix * window.cam.projMatrix * window.windowMatrix;

    finalTransformMatrixCube = Fern::Matrix4x4::RotationX(rotateSpeed) * Fern::Matrix4x4::RotationY(rotateSpeed * 2 / 3) * window.cam.viewMatrix * window.cam.projMatrix * window.windowMatrix;

    Fern::Matrix4x4 currentMovementMatrixCube2 = Fern::Matrix4x4::RotationX(-rotateSpeed) * Fern::Matrix4x4::RotationY(-rotateSpeed * 2 / 3);

    finalTransformMatrixCube2 =  Fern::Matrix4x4::RotationY(-rotateSpeed) * Fern::Matrix4x4::RotationZ(-rotateSpeed * 2 / 3) * Fern::Matrix4x4::Translation(0,0,-3) * window.cam.viewMatrix * window.cam.projMatrix * window.windowMatrix;
    int loop = 0;
    double rotateAngle = 0;

    //鼠标消息
    ExMessage msgMouse;

    //调试功能：显示坐标下深度值
    double depthXY;
    int wordHeight;
    int wordWidth;

    
    /*
    while (!window.ShouldClose()) {
        window.PollEvents();
        window.Clear();

        //finalTransformMatrixCube = Fern::Matrix4x4::RotationX(rotateSpeed) * Fern::Matrix4x4::RotationY(rotateSpeed * 2 / 3) * finalTransformMatrixCube;

        axisRenderDots = axis * finalTransformMatrixAxis;
        cubeRenderDots = cube * finalTransformMatrixCube;

        //立方体
        
        for (const auto& _ : cube.edges) {
            Fern::LineRender::DrawLine(&window,
                (int)cubeRenderDots[_.verticeStart].x, (int)cubeRenderDots[_.verticeStart].y,
                (int)cubeRenderDots[_.verticeEnd].x, (int)cubeRenderDots[_.verticeEnd].y,
                _.color);
        }

        
        for (const auto& _ : cube.surfaces) {
            Fern::Render::drawFillTriangle(&window,
                (int)cubeRenderDots[_.verticeA].x, (int)cubeRenderDots[_.verticeA].y,
                (int)cubeRenderDots[_.verticeB].x, (int)cubeRenderDots[_.verticeB].y,
                (int)cubeRenderDots[_.verticeC].x, (int)cubeRenderDots[_.verticeC].y,
                _.color);
        }
        
        




        for (const auto& _ : cube.surfaces) {
            Fern::Render::fastDrawFillTriangle(&window,
                cubeRenderDots[_.verticeA],
                cubeRenderDots[_.verticeB],
                cubeRenderDots[_.verticeC],
                _.color);
        }

        
        for (const auto& _ : cube.edges) {
            Fern::LineRender::DrawLine(&window,
                (int)cubeRenderDots[_.verticeStart].x, (int)cubeRenderDots[_.verticeStart].y,
                (int)cubeRenderDots[_.verticeEnd].x, (int)cubeRenderDots[_.verticeEnd].y,
                _.color);
        }
        
        
        for (const auto& _ : cube.edges) {
            Fern::LineRender::DrawLine(&window, 
                cubeRenderDots[_.verticeStart],
                cubeRenderDots[_.verticeEnd],
                _.color);
        }
        
        
        
        //坐标系
        for (const auto& _ : axis.edges) {
            Fern::LineRender::DrawLine(&window,
                axisRenderDots[_.verticeStart],
                axisRenderDots[_.verticeEnd],
                _.color);
        }

        //msgMouse = getmessage(EX_MOUSE);

        if (peekmessage(&msgMouse, EX_MOUSE));

        double depthXY = window.dep.currentDepthValue[msgMouse.x][msgMouse.y];

        oss6 << "(" << msgMouse.x << "," << msgMouse.y << "," << depthXY;
        std::wstring floatdepth = oss6.str();

        wordHeight = textheight((floatdepth.c_str()));
        wordWidth = textwidth(floatdepth.c_str());


        setbkcolor(Fern::Color::RimuluBlue().ToEasyXColor());
        
        fillrectangle(
            msgMouse.x - wordWidth - 13,
            msgMouse.y - wordHeight - 13,
            msgMouse.x - 8,
            msgMouse.y - 8
        );
        
        outtextxy(
            msgMouse.x - 8 - wordWidth,
            msgMouse.y - 8 - wordHeight,
            floatdepth.c_str()
        );

        oss6.str(L"");
        oss6.clear();

        setbkcolor(Fern::Color::Black().ToEasyXColor());

        window.Present();
        Sleep(16);

        rotateAngle += rotateSpeed;
        LOG_INFO("循环一次");
        oss5 << "已循环" << ++loop << "次，angle为" << rotateAngle << "弧度。";
        LOG_INFO(oss5.str());
        oss5.str("");
        oss5.clear();
    }
    */

    while (!window.ShouldClose()) {
        window.PollEvents();
        window.Clear();

        finalTransformMatrixCube = Fern::Matrix4x4::RotationX(rotateSpeed) * Fern::Matrix4x4::RotationY(rotateSpeed * 2 / 3) * finalTransformMatrixCube;

        finalTransformMatrixCube2 = Fern::Matrix4x4::RotationY(-rotateSpeed) * Fern::Matrix4x4::RotationZ(-rotateSpeed * 2 / 3) * finalTransformMatrixCube2;
        

        axisRenderDots = axis * finalTransformMatrixAxis;
        cubeRenderDots = cube * finalTransformMatrixCube;
        cube2RenderDots = cube2  * (finalTransformMatrixCube2);


        for (const auto& _ : cube.surfaces) {
            Fern::Render::fastDrawFillTriangle(&window,
                cubeRenderDots[_.verticeA],
                cubeRenderDots[_.verticeB],
                cubeRenderDots[_.verticeC],
                _.color);
        }

        for (const auto& _ : cube.edges) {
            Fern::LineRender::DrawLine3D(&window,
                cubeRenderDots[_.verticeStart],
                cubeRenderDots[_.verticeEnd],
                _.color);
        }
        
        for (const auto& _ : cube2.surfaces) {
            Fern::Render::fastDrawFillTriangle(&window,
                cube2RenderDots[_.verticeA],
                cube2RenderDots[_.verticeB],
                cube2RenderDots[_.verticeC],
                _.color);
        }
        
        //深度图着色模式
        /*
        for (int x = 0;x < window.Width();x++) {
            for (int y = 0;y < window.Height();y++) {
                double currentDepth = window.dep.currentDepthValue[y][x];
                Fern::Color _ = colorInsert(Fern::Color::Black(), Fern::Color::RimuluBlue(), currentDepth);

                putpixel(x, y, _.ToEasyXColor());
            }
        }
        */
        window.Present();
    }

	LOG_INSTANCE.stop();
	return 0;
}

