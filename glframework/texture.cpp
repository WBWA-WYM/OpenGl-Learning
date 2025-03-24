#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"
Texture::Texture(const std::string& path, unsigned int uint)
{
	mUint = uint;
	//1 stb image读取图片
	int mWidth, mHeight, channels;

	//反转y轴
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

	//2 生成纹理并且激活单元绑定
	glGenTextures(1, &mTexture);
	//--激活纹理单元
	glActiveTexture(GL_TEXTURE0 + mUint);
	//绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//3传输数据,开辟显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//遍历每个mipmap的层级，为每个级别的mipmap填充图片数据
	//int width = mWidth;
	//int height = mHeight;

	//for (int level = 0; true; ++level) {
	//	//1 将当前级别的mipmap对应的数据发往gpu端
	//	glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE,data);
	//	//2判断是否退出循环
	//	if (width == 1 && height == 1) {
	//		break;
	//	}
	//	
	//	//3 计算下一次的循环的宽度/高度，除以2
	//	width = width > 1 ? width / 2 : 1;
	//	height = height > 1 ? height / 2 : 1;

	//}
	
	
	//释放数据
	stbi_image_free(data);

	//4 设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	//5设置纹理的包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u方向
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v方向
}

Texture::~Texture()
{
	if (mTexture != 0)
	{
		glDeleteTextures(1, &mTexture);
	}
}

void Texture::bind()
{
	//先激活自家纹理单元，再绑定纹理对象
	glActiveTexture(GL_TEXTURE0 + mUint);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}
