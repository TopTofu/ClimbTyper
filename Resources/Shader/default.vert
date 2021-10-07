#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 camera;

out vec2 TexCoord;

void main()
{
	gl_Position = camera * transform * vec4(aPos, 1.0f);	
	TexCoord = aTexCoord;
}