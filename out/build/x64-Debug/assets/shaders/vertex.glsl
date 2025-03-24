#version 460 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec2 aUV;

out vec3 color;
out vec2 uv;
uniform sampler2D Sampler;
uniform float time;

uniform mat4 viewMatrix;
uniform mat4 orthoMatrix;
uniform mat4 perspectiveMatrix;



//aPos作为attribute（属性）
//不允许更改的
void main()
{
// 1当前三角形顶点，缩放的比例
//float scale = 1.0 / time;

//2使用scale对顶点位置进行缩放
//vec3 sPos = aPos*scale;

//3 向后传输位置信息
vec4 position = vec4(aPos,1.0);
position = perspectiveMatrix*viewMatrix*position;
gl_Position = position;
uv = aUV;
}