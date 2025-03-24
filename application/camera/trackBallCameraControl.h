#pragma once

#include "cameraControl.h"

class TrackBallCameraControl : public CameraControl {
public:
	TrackBallCameraControl();
	~TrackBallCameraControl();
	//父类中的接口函数是否需要重写
	void onCursor(double xpos, double ypos) override;
	void onScroll(float offset) override;//+1 -1
private:
	float mCurrentY;
	float mCurrentX;
	float mMoveSpeed = 0.005f;
private:
	void pitch(float angle);
	void yaw(float angle);
};	