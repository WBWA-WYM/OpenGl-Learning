#pragma once
#include <iostream>
#include "camera.h"
#include <map>

class CameraControl {
public:
	CameraControl();
	~CameraControl();
	//继承CameraControl的子类，有可能会实现自己的逻辑 
	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float offset);//+1 -1

	//每一帧渲染之前都要进行，每一帧的更新的行为可以放在这里
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float s) { mSensitivity = s; }
	void setScaleSpeed(float s) { mScaleSpeed = s; }


protected:
	//1 鼠标按键状态
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	//2鼠标位置
	float mCurrentX = 0.0f, mCurrentY = 0.0f;

	//3敏感度
	float mSensitivity = 0.2f;

	//4记录键盘相关按键的按下状态
	std::map<int, bool> mKeyMap;

	//5存储当前控制的那一个摄像机
	Camera* mCamera = nullptr;

	//6记录相机缩放的速度
	float mScaleSpeed = 0.2f;
};