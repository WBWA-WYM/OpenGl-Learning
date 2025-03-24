#version 460 core
out vec4 FragColor;

in vec2 uv;

uniform sampler2D Sampler;

uniform float width;
uniform float height;

void main()
{
FragColor = texture(Sampler,uv);
}