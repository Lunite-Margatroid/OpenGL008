#include "render.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "SpotLight.h"
#include "Model.h"
#include "FrameBuffer.h"
#include "TextureCube.h"
#include "UniformBuffer.h"
#include "Camera_K.h"
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <map>

// 函数声明
GLFWwindow* InitGL();
void UpdateTimer();
void ProcessInput(GLFWwindow* window);
void RuntimeLog();
// 全局变量
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

LM::Camera_K camera;

// 关于实例化的练习
int main()
{
	GLFWwindow* window = InitGL();

	// 混合configuration
	//GLCall(glEnable(GL_BLEND));
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 面剔除
	// GLCall(glEnable(GL_CULL_FACE));

	GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
	float screenQuad[] =
	{
		-1.0f, -1.0f,		0.0f, 0.0f,
		1.0f, -1.0f,		1.0f, 0.0f,
		1.0f, 1.0f,			1.0f, 1.0f,
		-1.0f, 1.0f,		0.0f, 1.0f
	};

	unsigned int screenIndex[] =
	{
		0,1,2,0,2,3
	};

	float points[] =
	{	// Coord				Color
		-0.07f, -0.07f,		0.1f, 0.9f, 0.2f,
		0.07f, -0.07f,		0.1f, 0.9f, 0.2f,
		0.07f, 0.07f,		0.1f, 0.9f, 0.2f,
		-0.07f, 0.07f,		0.1f, 0.9f, 0.2f
	};

	float onePoint[5] = { 0.0f, 0.0f, 0.1f, 0.8f, 0.05f };

	float offsets[200];
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			offsets[i * 20 + j * 2] = -1.f + i * 0.2f;
			offsets[i * 20 + j * 2 + 1] = -1.f + j * 0.2f;
		}

	{
		LM::VertexArray screen;
		screen.AddBuffer(4, 4, screenQuad);
		screen.AddElementBuffer(6, screenIndex);
		screen.PushAttrib(2);
		screen.PushAttrib(2);
		screen.ApplyLayout();
		LM::FrameBuffer screenFrameBuffer(WIDTH, HEIGHT);
		LM::Shader texShader("./res/shader/TexVertex.shader", "./res/shader/TexFragment.shader");

		LM::VertexArray vaOnePoint;
		vaOnePoint.AddBuffer(1, 5, onePoint);
		vaOnePoint.PushAttrib(2);
		vaOnePoint.PushAttrib(3);
		vaOnePoint.ApplyLayout();
		vaOnePoint.SetElementType(GL_POINTS);
		LM::Shader sdrOnePoint("./res/shader/OnePointVertex.shader",
			"./res/shader/OnePointFragment.shader",
			"./res/shader/OnePointGeometry.shader");
		/*LM::Shader sdrOnePoint("./res/shader/OnePointVertex.shader",
			"./res/shader/OnePointFragment.shader");*/
		sdrOnePoint.UniformBlockBinding("offsets", 0);
		LM::UniformBuffer uboOffset(sizeof(offsets), offsets);
		uboOffset.BindBufferBase(0);

		while (!glfwWindowShouldClose(window))
		{

			glm::mat4 viewTrans = camera.GetViewTrans();
			glm::mat4 projectionTrans = camera.GetProjectionTrans();
			glm::mat4 modelTrans = glm::mat4(1.0f);
			glm::vec3 cameraPos = camera.GetPosition();
			// 法向量矩阵  变换矩阵的逆的转置
			// glm::mat3 normalMat = glm::mat3(transpose(inverse(modelTrans)));

			screenFrameBuffer.Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// ------------Draw Here------------------//
			sdrOnePoint.Bind();
			vaOnePoint.DrawArraysInstanced(100);

			// ------------Draw End--------------------//
			screenFrameBuffer.Unbind();
			glDisable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT);
			texShader.Bind();
			texShader.SetUniformTexture("tex", screenFrameBuffer.GetTexIndex());
			screen.DrawElement();

			glfwSwapBuffers(window);
			// log
			RuntimeLog();
			// 更新时间变量
			UpdateTimer();
			// 处理键盘控制输入
			ProcessInput(window);
			// 检查触发事件
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}

// 回调函数 改变窗口大小和位置时 重新设置视口
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.ProcessMouse(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double offsetx, double offsety)
{
	camera.ProcessScroll(offsety);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

}

// 处理键盘交互
void ProcessInput(GLFWwindow* window)
{
	// 检测esc按下，则关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	camera.ProcessKeyInput(window, deltaTime);
}

void UpdateTimer()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void RuntimeLog()
{
	static glm::vec3 cameraPos = camera.GetPosition();
	cameraPos = camera.GetPosition();

	std::cout << "Camera current position:" << '(' << cameraPos.x << ',' << cameraPos.y
		<< ',' << cameraPos.z << ")                " << std::endl;

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;
	GetConsoleScreenBufferInfo(hOut, &cursorInfo);
	coord = cursorInfo.dwCursorPosition;
	coord.X = 0;
	coord.Y -= 1;
	SetConsoleCursorPosition(hOut, coord);
}


GLFWwindow* InitGL()
{
	// 初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 初始化窗口
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL009", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// 生成上下文
	glfwMakeContextCurrent(window);

	// 加载opengl函数 要在生成上下文之后
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to initialize glad" << std::endl;
		glfwTerminate();
		return NULL;
	}
	// 开启垂直同步
	glfwSwapInterval(1);

	// 设置视口
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));

	// 捕捉cursor
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 声明回调函数
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void scroll_callback(GLFWwindow * window, double offsetx, double offsery);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

	void ProcessInput(GLFWwindow * window);
	// 注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// 深度测试选项
	GLCall(glEnable(GL_DEPTH_TEST));					// 开启深度检测
	//GLCall(glDepthMask(GL_FALSE));						// 只读深度缓冲
	GLCall(glDepthFunc(GL_LESS));						// 深度缓冲通过条件  默认为less


	// 模版缓冲选项
	// GLCall(glEnable(GL_STENCIL_TEST));

	GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.f));			// 清屏颜色

	// stbi_set_flip_vertically_on_load(true);
	return window;
}