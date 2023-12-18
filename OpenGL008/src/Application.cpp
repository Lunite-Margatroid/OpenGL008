#include "render.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "SpotLight.h"
#include "Model.h"
#include "FrameBuffer.h"
#include "TextureCube.h"
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <map>

// ��������
GLFWwindow* InitGL();
void UpdateTimer();
void ProcessInput(GLFWwindow* window);
void RuntimeLog();
// ȫ�ֱ���
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

LM::Camera camera;


int main()
{
	GLFWwindow* window = InitGL();

	// ���configuration
	//GLCall(glEnable(GL_BLEND));
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���޳�
	// GLCall(glEnable(GL_CULL_FACE));

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

	std::vector<std::string> skyboxPath =
	{
		"./res/tex/right.jpg",
		"./res/tex/left.jpg",
		"./res/tex/top.jpg",
		"./res/tex/bottom.jpg",
		"./res/tex/front.jpg",
		"./res/tex/back.jpg"
	};
	float left = 0.0f;
	float bottom = 1.0f;
	float right = 1.0f;
	float top = 0.0f;
	float cubeVertice[]
	{
		-1.0f, -1.0f, 1.0f,		left, bottom,
		1.0f, -1.0f, 1.0f,		right, bottom,
		1.0f, 1.0f, 1.0f,		right, top,
		-1.0f, 1.0f, 1.0f,		left, top,

		-1.0f, -1.0f, -1.0f,	left, bottom,
		-1.0f, 1.0f, -1.0f,		right, bottom,
		1.0f, 1.0f, -1.0f,		right, top,
		1.0f, -1.0f, -1.0f,		left, top,

		 -1.0f, 1.0f,-1.0f,		left, bottom,
		 -1.0f, 1.0f,1.0f,		right, bottom,
		 1.0f, 1.0f,1.0f,		right, top,
		 1.0f, 1.0f,-1.0f,		left, top,

		 -1.0f, -1.0f,-1.0f,	left, bottom,
		 1.0f, -1.0f,-1.0f,		right, bottom,
		1.0f, -1.0f,1.0f,		right, top,
		-1.0f, -1.0f,1.0f,		left, top,

		1.0f,-1.0f, -1.0f,		left, bottom,
		1.0f,1.0f, -1.0f,		right, bottom,
		1.0f,1.0f, 1.0f,		right, top,
		1.0f,-1.0f, 1.0f,		left, top,

		-1.0f,-1.0f, -1.0f,		left, bottom,
		-1.0f,-1.0f, 1.0f,		right, bottom,
		-1.0f,1.0f, 1.0f,		right, top,
		-1.0f,1.0f, -1.0f,		left, top
	};

	float cubeVertice0[]
	{
		-1.0f, -1.0f, 1.0f,		
		1.0f, -1.0f, 1.0f,		
		1.0f, 1.0f, 1.0f,		
		-1.0f, 1.0f, 1.0f,		

		-1.0f, -1.0f, -1.0f,	
		-1.0f, 1.0f, -1.0f,		
		1.0f, 1.0f, -1.0f,		
		1.0f, -1.0f, -1.0f,		

		 -1.0f, 1.0f,-1.0f,		
		 -1.0f, 1.0f,1.0f,		
		 1.0f, 1.0f,1.0f,		
		 1.0f, 1.0f,-1.0f,		

		 -1.0f, -1.0f,-1.0f,	
		 1.0f, -1.0f,-1.0f,		
		1.0f, -1.0f,1.0f,		
		-1.0f, -1.0f,1.0f,		

		1.0f,-1.0f, -1.0f,		
		1.0f,1.0f, -1.0f,		
		1.0f,1.0f, 1.0f,		
		1.0f,-1.0f, 1.0f,		

		-1.0f,-1.0f, -1.0f,		
		-1.0f,-1.0f, 1.0f,		
		-1.0f,1.0f, 1.0f,		
		-1.0f,1.0f, -1.0f
	};


	float cubeVertice1[]
	{	// ����						������
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,

		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,

		 -1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,
		 -1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 1.0f,1.0f,		0.0f, 1.0f, 0.0f,
		 1.0f, 1.0f,-1.0f,		0.0f, 1.0f, 0.0f,

		 -1.0f, -1.0f,-1.0f,	0.0f, -1.0f, 0.0f,
		 1.0f, -1.0f,-1.0f,		0.0f, -1.0f, 0.0f,
		1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f,1.0f,		0.0f, -1.0f, 0.0f,

		1.0f,-1.0f, -1.0f,		1.0f, 0.0f,  0.0f,
		1.0f,1.0f, -1.0f,		1.0f, 0.0f,  0.0f,
		1.0f,1.0f, 1.0f,		1.0f, 0.0f,  0.0f,
		1.0f,-1.0f, 1.0f,		1.0f, 0.0f,  0.0f,

		-1.0f,-1.0f, -1.0f,		-1.0f, 0.0f,  0.0f,
		-1.0f,-1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,
		-1.0f,1.0f, 1.0f,		-1.0f, 0.0f,  0.0f,
		-1.0f,1.0f, -1.0f,		-1.0f, 0.0f,  0.0f
	};
	unsigned int cubeIndice[36] = { 0, 1, 2, 2, 3, 0 };
	for (unsigned int i = 6; i < 36; i++)
	{
		cubeIndice[i] = cubeIndice[i - 6] + 4;
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

		LM::VertexArray skybox;
		skybox.AddBuffer(24, 3, cubeVertice0);
		skybox.AddElementBuffer(36, cubeIndice);
		skybox.PushAttrib(3);
		skybox.ApplyLayout();
		LM::Shader skyboxShader("./res/shader/SkyboxVertex.shader", "./res/shader/SkyboxFragment.shader");
		
		LM::TextureCube skyboxTex(skyboxPath, 0, GL_RGB, GL_RGB);

		LM::VertexArray cube;
		cube.AddBuffer(24, 5, cubeVertice);
		cube.AddElementBuffer(36, cubeIndice);
		cube.PushAttrib(3);
		cube.PushAttrib(2);
		cube.ApplyLayout();
		LM::Texture texCube("./res/tex/Sakuya.bmp", 0, GL_RGB, GL_RGB);
		LM::Shader shader1("./res/shader/N1Vertex.shader", "./res/shader/N1Fragment.shader");

		LM::VertexArray glassCube;
		glassCube.AddBuffer(24, 6, cubeVertice1);
		glassCube.AddElementBuffer(36, cubeIndice);
		glassCube.PushAttrib(3);
		glassCube.PushAttrib(3);
		glassCube.ApplyLayout();
		LM::Shader glassShader("./res/shader/ReflVertex.shader","./res/shader/ReflFragment.shader");

		LM::Shader refrShader("./res/shader/RefrVertex.shader","./res/shader/RefrFragment.shader");
		while (!glfwWindowShouldClose(window))
		{

			glm::mat4 viewTrans = camera.GetViewTrans();
			glm::mat4 projectionTrans = camera.GetProjectionTrans();
			glm::mat4 modelTrans = glm::mat4(1.0f);
			glm::vec3 cameraPos = camera.GetPosition();
			// ����������  �任��������ת��
			// glm::mat3 normalMat = glm::mat3(transpose(inverse(modelTrans)));

			screenFrameBuffer.Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			// ------------Draw Here------------------//
			
			

			shader1.Bind();
			shader1.SetUniformMatrix4f("modelTrans", false, glm::value_ptr(modelTrans));
			shader1.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewTrans));
			shader1.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));
			texCube.Bind();
			shader1.SetUniformTexture("tex", texCube.GetIndex());
			cube.DrawElement();

			glassShader.Bind();
			modelTrans = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, 5.0f));
			glassShader.SetUniformMatrix4f("modelTrans", false, glm::value_ptr(modelTrans));
			glassShader.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewTrans));
			glassShader.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));
			glm::mat3 normalMat = glm::mat3(transpose(inverse(modelTrans)));
			glassShader.SetUniformMatrix3f("normalMat", false, glm::value_ptr(normalMat));
			glassShader.SetUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
			texCube.Bind();
			glassShader.SetUniformTexture("cubeTex", skyboxTex.GetIndex());
			glassCube.DrawElement();

			refrShader.Bind();
			modelTrans = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0.0f, -5.0f));
			refrShader.SetUniformMatrix4f("modelTrans", false, glm::value_ptr(modelTrans));
			refrShader.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewTrans));
			refrShader.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));
			normalMat = glm::mat3(transpose(inverse(modelTrans)));
			refrShader.SetUniformMatrix3f("normalMat", false, glm::value_ptr(normalMat));
			refrShader.SetUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
			texCube.Bind();
			refrShader.SetUniformTexture("cubeTex", skyboxTex.GetIndex());
			glassCube.DrawElement();


			// ������պ�
			glDepthFunc(GL_EQUAL | GL_LESS);	// ��պе���Ⱥ����1
			skyboxShader.Bind();
			glm::mat4 viewtemp = glm::mat4(glm::mat3(viewTrans));
			skyboxShader.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewtemp));
			skyboxShader.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));
			skyboxTex.Bind();
			skyboxShader.SetUniformTextureCube("cubeTex", skyboxTex.GetIndex());
			skybox.DrawElement();
			glDepthFunc(GL_LESS);
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
			// ����ʱ�����
			UpdateTimer();
			// ������̿�������
			ProcessInput(window);
			// ��鴥���¼�
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}

// �ص����� �ı䴰�ڴ�С��λ��ʱ ���������ӿ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMouse = true;
	static float lastX = WIDTH / 2;
	static float lastY = HEIGHT / 2;

	if (firstMouse)
	{
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}

	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;

	camera.ProcessMouse(offsetX, offsetY);

	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double offsetx, double offsety)
{
	camera.ProcessScroll(offsety);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

}

// ������̽���
void ProcessInput(GLFWwindow* window)
{
	// ���esc���£���رմ���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::FRONT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::BACK, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::DOWN, deltaTime);
	}
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
	// ��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��ʼ������
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL007", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// ����������
	glfwMakeContextCurrent(window);

	// ����opengl���� Ҫ������������֮��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to initialize glad" << std::endl;
		glfwTerminate();
		return NULL;
	}
	// ������ֱͬ��
	glfwSwapInterval(1);

	// �����ӿ�
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));

	// ��׽cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// �����ص�����
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void scroll_callback(GLFWwindow * window, double offsetx, double offsery);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

	void ProcessInput(GLFWwindow * window);
	// ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// ��Ȳ���ѡ��
	GLCall(glEnable(GL_DEPTH_TEST));					// ������ȼ��
	//GLCall(glDepthMask(GL_FALSE));						// ֻ����Ȼ���
	GLCall(glDepthFunc(GL_LESS));						// ��Ȼ���ͨ������  Ĭ��Ϊless


	// ģ�滺��ѡ��
	// GLCall(glEnable(GL_STENCIL_TEST));

	GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.f));			// ������ɫ

	// stbi_set_flip_vertically_on_load(true);
	return window;
}