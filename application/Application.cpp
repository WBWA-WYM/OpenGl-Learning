#include "Application.h"
#include "Application.h"
#include "Application.h"
#include "Application.h"
#include "Application.h"
#include "Application.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//初始化Application的静态变量
Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//如果mInstance已经实例化了，（new出来），就直接返回
	//否则需要先new出来，再返回
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	return mInstance;
}
bool Application::init(const int& width, const int& height)
{
	mWidth = width;
	mHeight = height;
	
	//1.1初始化GLFW基本环境
	glfwInit();
	//1.2设置OPENGL主版本号，次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.3启用OpenGL核心模式(非立即渲染模式)	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//2.1创建窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}
	//2.2设置为OPENGL绘制舞台
	glfwMakeContextCurrent(mWindow);
	//使用glad加载所有当前版本的opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	//GL监听
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	glfwSetKeyCallback(mWindow, keyCallback);
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	glfwSetCursorPosCallback(mWindow, cursorCallback);
	glfwSetScrollCallback(mWindow, scrollCallback);

	//this就是当前全局唯一Application对象
	glfwSetWindowUserPointer(mWindow, this);
	return true;
}
bool Application::update()
{
	//执行窗体循环
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	
		glfwPollEvents();

		//切换双缓存
		glfwSwapBuffers(mWindow);
	

}
void Application::destroy()
{
	//退出前做相关清理
	glfwTerminate();
}
void Application::getCursorPosition(double* x, double* y)
{
	glfwGetCursorPos(mWindow,x,y);
}
void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr) {
		self->mResizeCallback(width, height);
	}
	//if(Application::getInstance()->mResizeCallback !=nullptr)
	//Application::getInstance()->mResizeCallback(width, height);
}
void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyBoardCallback != nullptr)
	{
		self->mKeyBoardCallback(key, action, mods);
	}
}
void Application::cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mCursorCallback != nullptr) {
		self->mCursorCallback(xpos, ypos);
	}
}
void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mMouseCallback != nullptr) {
		self->mMouseCallback(button,action,mods);
	}
}
void Application::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mScrollCallback != nullptr) {
		self->mScrollCallback(yoffset);//只有y方向滚轮可以转动
	}
}
Application::~Application()
{
}

Application::Application()
{

}
