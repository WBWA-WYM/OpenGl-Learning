#include "cameraControl.h"
#include "camera.h"
#include "cameraControl.h"

CameraControl::CameraControl()
{
}

CameraControl::~CameraControl()
{
}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{	//1 判断当前的按键，是否按下
	bool pressed = (action == GLFW_PRESS)? true : false;

	//2 如果按下，记录当前按下的位置
	if (pressed) {
		mCurrentX = xpos;
		mCurrentY = ypos;
	}

	//3 根据按下的鼠标按键不同，更改按键状态
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos)
{
}

void CameraControl::onKey(int key, int action, int mods)
{
	//过滤掉REPEAT的情况
	if (action == GLFW_REPEAT) {
		return;
	}
	// 1检测按下或者抬起，给到一个变量
	bool pressed = (action == GLFW_PRESS) ? true : false;

	// 2记录在keyMap里
	mKeyMap[key] = pressed;
}

void CameraControl::onScroll(float offset)
{

}

void CameraControl::update()
{
}
