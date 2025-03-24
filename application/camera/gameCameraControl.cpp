#include "gameCameraControl.h"
#include "gameCameraControl.h"

GameCameraControl::GameCameraControl()
{
}

GameCameraControl::~GameCameraControl()
{
}

void GameCameraControl::onCursor(double xpos, double ypos)
{
	float deltaX = (xpos - mCurrentX) * mSensitivity;
	float deltaY = (ypos - mCurrentY) * mSensitivity;

	if (mRightMouseDown)
	{
		pitch(-deltaY);
		yaw(-deltaX);
	}
	mCurrentX = xpos;
	mCurrentY = ypos;
}

void GameCameraControl::update()
{
	//最终移动方向
	glm::vec3 direction(0.0f);

	auto front = glm::cross(mCamera->mUp, mCamera->mRight);
	auto right = mCamera->mRight;

	if (mKeyMap[GLFW_KEY_W]) {
		direction += front;	
	}
	if (mKeyMap[GLFW_KEY_S]) {
		direction -= front;
	}
	if (mKeyMap[GLFW_KEY_A]) {
		direction -= right;
	}
	if (mKeyMap[GLFW_KEY_D]) {
		direction += right;
	}

	//此时direction 有可能不为1 可能为0
	if (glm::length(direction) != 0) {
		direction = glm::normalize(direction);
		mCamera->mPosition += direction * mSpeed;
	}

}

void GameCameraControl::pitch(float angle)
{
	/*mPitch += angle;
	if ((mPitch > 179.0f) || (mPitch < -179.0f)) {
		mPitch -= angle;
		return;
	}*/
	//在GameCamera的情况下，pitch不会影响到mPosition
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);	
}

void GameCameraControl::yaw(float angle)
{	/*mYaw += angle;
	if ((mYaw > 179.0f) || (mYaw < -179.0f)) {
		mYaw -= angle;
		return;
	}*/
	//在GameCamera的情况下，mYaw影响right up
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle),mCamera->mUp);
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);

}
