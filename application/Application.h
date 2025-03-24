#pragma once
#include <iostream>
#define app Application::getInstance()

struct GLFWwindow;
class Application {
public:
	~Application();
	//用于访问实例的静态函数
	static Application* getInstance();
	bool init(const int& width = 800, const int& height = 600);
	bool update();
	void destroy();
	
	using ResizeCallback = void(*)(int width, int height);
	using Keyboardcallback = void(*)(int key,int action, int mods);
	using MouseCallback = void(*)(int button, int action, int mods);
	using CursorCallback = void(*)(double xpos, double ypos);
	using ScrollCallback = void(*)(double offset);


	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }
	void getCursorPosition(double *x,double *y);

	//外界设置哪个函数实现监听
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setReKeyboard(Keyboardcallback callback) { mKeyBoardCallback = callback; }
	void setMouseCallback(MouseCallback callback) { mMouseCallback = callback; }
	void setCursorCallback(CursorCallback callback) { mCursorCallback = callback; }
	void setScrollCallback(ScrollCallback callback) { mScrollCallback = callback; }


private:
	//C++类内函数指针
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double xoffset,double yoffset);

private:
	//全局唯一的静态变量实例	
	static Application* mInstance;

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
	//函数指针生成对象
	ResizeCallback mResizeCallback{ nullptr };
	Keyboardcallback mKeyBoardCallback{ nullptr };
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };
	Application();
};