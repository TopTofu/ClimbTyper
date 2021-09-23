#version 330 core

out vec4 frag_color;

in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
	frag_color = texture(Texture, TexCoord);
	//frag_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}