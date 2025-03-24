#include "camera.h"
#include "camera.h"
#include <iostream>
//可以在这里把初始化参数都传进来
Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{	//lookat
	//-eye:相机位置(mPosition)
	//-center:看向世界坐标的哪个点
	//-top：穹顶（mUp替代)
	glm::vec3 front = glm::cross(mRight, mUp);
	front = -front;
	glm::vec3 center = mPosition + front;
	return glm::lookAt(mPosition,center,mUp);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::identity<glm::mat4>();
}

void Camera::scale(float deltaScale)
{
}
