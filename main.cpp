#include <iostream>
//glad头文件在glfw引用之前
#include "glframework/core.h"
#include "glframework/shader.h"
#include <assert.h>
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/texture.h"
//引入相机＋控制器
#include "application/camera/perspectiveCamera.h"
#include "application/camera/trackBallCameraControl.h"

#include "application/camera/orthographicCamera.h"
#include "application/camera/gameCameraControl.h"
#include "glframework/geometry.h"

Geometry* geometry = nullptr;
Shader* shader = nullptr;
Texture* texture1 = nullptr;
Texture* texture2 = nullptr;
PerspectiveCamera* camera = nullptr;
GameCameraControl* cameraControl = nullptr;
//OrthographicCamera* camera = nullptr;
//回调
void OnResize(int width, int height) {
	GL_CALL (glViewport(0, 0, width, height));
}
void OnRekeyboard(int key,int action, int mods) {
	cameraControl->onKey(key, action, mods);
}
void OnMouse(int button, int action, int mods){
	double x, y;
	app->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}
void OnCursor(double xpos, double ypos){
	cameraControl->onCursor(xpos, ypos);
}
void OnScroll(double offset) {
	cameraControl->onScroll(offset);
}
void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl","assets/shaders/fragment.glsl");
}	
void prepareTexture() {	
	texture1 = new Texture("assets/textures/tex.jpg",0);
	texture2 = new Texture("C:/Users/王已萌/Desktop/01 GLFW_Window/assets/textures/title00a.png",1);
}
void render() {
	//opengl画布清理操作
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//1绑定当前的program
	shader->begin();
	shader->setInt("Sampler", 0);
	//shader->setFloat("time", glfwGetTime());
	shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
	shader->setMatrix4x4("perspectiveMatrix", camera->getProjectionMatrix());
	//2绑定当前的vao1
	glBindVertexArray(geometry->getVao());
	//3发出绘制指令
	glDrawElements(GL_TRIANGLES,geometry->getIndicesCount(),GL_UNSIGNED_INT,0);
	shader->end();
}
void prepareCamera() {
	camera = new PerspectiveCamera(
		60.0f, (float)app->getWidth() / (float)app->getHeight(),
		0.1f,
		1000.0f); 
	/*float size = 3.0f;
	camera = new OrthographicCamera(-size, size,-size,size,0.1f, 1000.0f);*/
	cameraControl = new GameCameraControl();
	cameraControl->setCamera(camera);
}
void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
void prepareVAO() {
	geometry = Geometry::createBox(1.0f);
}
int main() {
	if (!app->init(800, 600)) {
		return -1;
	}
	app->setResizeCallback(OnResize);
	app->setReKeyboard(OnRekeyboard);
	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);
	app->setScrollCallback(OnScroll);

	//设置opengl视口，清理颜色
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	prepareShader();
	prepareVAO();
	prepareTexture();
	prepareCamera();
	prepareState();
	//doRotationTransform();
	/*doTranslationTransform();*/
	

	//3执行窗体循环	
	while (app->update())
	{

		cameraControl->update();
		/*doRotation();*/
		render();
	}
	//4退出前清理
	app->destroy();
	//delete grasstexture;
	//delete landtexture;
	return 0;
}