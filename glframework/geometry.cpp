#include "geometry.h"
#include <vector>
Geometry::Geometry()
{
}

Geometry::~Geometry()
{
	if (mVao != 0) {
		glDeleteVertexArrays(1, &mVao);
	}
	if (mPosVbo != 0) {
		glDeleteBuffers(1, &mPosVbo);
	}
	if (mUvVbo != 0) {
		glDeleteBuffers(1, &mUvVbo);
	}
	if (mEbo != 0) {
		glDeleteBuffers(1, &mEbo);
	}
}

Geometry* Geometry::createBox(float size)
{
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 36;
	float halfSize = size / 2.0f;
	//1 准备数据
	float positions[] = {
		// 前面
	// 前面
	-0.5f, -0.5f,  0.5f,  // 左下
	 0.5f, -0.5f,  0.5f,  // 右下
	 0.5f,  0.5f,  0.5f,  // 右上
	-0.5f,  0.5f,  0.5f,  // 左上

	// 后面
	-0.5f, -0.5f, -0.5f,  // 左下
	 0.5f, -0.5f, -0.5f,  // 右下
	 0.5f,  0.5f, -0.5f,  // 右上
	-0.5f,  0.5f, -0.5f,  // 左上

	// 左面
	-0.5f, -0.5f, -0.5f,  // 左下
	-0.5f, -0.5f,  0.5f,  // 左下
	-0.5f,  0.5f,  0.5f,  // 左上
	-0.5f,  0.5f, -0.5f,  // 左上

	// 右面
	 0.5f, -0.5f, -0.5f,  // 右下
	 0.5f, -0.5f,  0.5f,  // 右下
	 0.5f,  0.5f,  0.5f,  // 右上
	 0.5f,  0.5f, -0.5f,  // 右上

	 // 上面
	 -0.5f,  0.5f, -0.5f,  // 左下
	  0.5f,  0.5f, -0.5f,  // 右下
	  0.5f,  0.5f,  0.5f,  // 右上
	 -0.5f,  0.5f,  0.5f,  // 左上

	 // 下面
	 -0.5f, -0.5f, -0.5f,  // 左下
	  0.5f, -0.5f, -0.5f,  // 右下
	  0.5f, -0.5f,  0.5f,  // 右上
	 -0.5f, -0.5f,  0.5f   // 左上
	};

	float uvs[] = {
		// 前面
   0.0f, 0.0f,  // 0
   1.0f, 0.0f,  // 1
   1.0f, 1.0f,  // 2
   0.0f, 1.0f,  // 3

   // 后面
   0.0f, 0.0f,  // 4
   1.0f, 0.0f,  // 5
   1.0f, 1.0f,  // 6
   0.0f, 1.0f,  // 7

   // 左面
   0.0f, 0.0f,  // 8
   1.0f, 0.0f,  // 9
   1.0f, 1.0f,  // 10
   0.0f, 1.0f,  // 11

   // 右面
   0.0f, 0.0f,  // 12
   1.0f, 0.0f,  // 13
   1.0f, 1.0f,  // 14
   0.0f, 1.0f,  // 15

   // 上面
   0.0f, 0.0f,  // 16
   1.0f, 0.0f,  // 17
   1.0f, 1.0f,  // 18
   0.0f, 1.0f,  // 19

   // 下面
   0.0f, 0.0f,  // 20
   1.0f, 0.0f,  // 21
   1.0f, 1.0f,  // 22
   0.0f, 1.0f   // 23
	};

	unsigned int indices[] = {
		// 前面
   0, 1, 2, 0, 2, 3,
   // 后面
   4, 5, 6, 4, 6, 7,
   // 左面
   8, 9, 10, 8, 10, 11,
   // 右面
   12, 13, 14, 12, 14, 15,
   // 上面
   16, 17, 18, 16, 18, 19,
   // 下面
   20, 21, 22, 20, 22, 23
	};

	//2 VBO创建
	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVbo;
	glGenBuffers(1,&posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(positions),positions,GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	//3 EBO创建
	glGenBuffers(1,&geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//4 VAO创建
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

		//4.2灌数据
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(unsigned int) * 2, (void*)0);

	//5加入EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,geometry->mEbo);

	glBindVertexArray(0);


	return geometry;
}

Geometry* Geometry::createSphere(float size)
{
	Geometry* geometry = new Geometry();

	//1位置 2uv 3索引
	//1主要变量声明
	std::vector<GLfloat>positions{};
	std::vector<GLfloat>uvs{};
	std::vector<unsigned int>indices{};
	//声明纬线和经线的数量
	int  numLatiLines = 60;//纬线
	int  numLongLines = 60;//经线
	
	//2通过两层循环（纬线在外，经线在内）生成位置 uv
	for (int i = 0; i <= numLatiLines; i++) {
		for (int j = 0; j <= numLongLines; j++) {
			float phi = i * glm::pi<float>() / numLatiLines;
			float theta = 2 * j * glm::pi<float>() / numLongLines;

			float y = size * cos(phi);
			float x = size * sin(phi) * cos(theta);
			float z = size * sin(phi) * sin(theta);

			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);

			float u = 1.0f - (float)j / (float)numLongLines;
			float v = 1.0f - (float)i / (float)numLatiLines;

			uvs.push_back(u);
			uvs.push_back(v);
		}
	}
	//3 通过两层循环（这里没有=号） 顶点索引
	for (int i = 0; i < numLatiLines; i++) {
		for (int j = 0; j < numLongLines; j++) {
			int p1 = i * (numLongLines + 1) + j;
			int p2 = p1 + numLongLines + 1;
			int p3 = p1 + 1;
			int p4 = p2 + 1;

			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);

			indices.push_back(p3);
			indices.push_back(p2);
			indices.push_back(p4);
		}

	}
	//4生成vbo和vao
	GLuint& posVbo = geometry->mPosVbo, uvVbo = geometry->mUvVbo;
	geometry->mIndicesCount = indices.size();
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size()* sizeof(GLfloat), positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER,uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	glBindVertexArray(0);
	return geometry;
}	
