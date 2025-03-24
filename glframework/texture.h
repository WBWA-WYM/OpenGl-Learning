#pragma once
#include <string>
#include "core.h"
class Texture {
public:
	Texture(const std::string& path,unsigned int uint);
	~Texture();
	void bind();

	int getWidth()const { return mWidth; }
	int getHeight()const { return mHeight; }

private:
	GLuint mTexture{0};
	int mWidth{0};
	int mHeight{0};
	unsigned int mUint{ 0 };

};