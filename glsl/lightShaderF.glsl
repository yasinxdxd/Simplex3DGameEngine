#version 330 core

out vec4 frag_color;
out vec4 light_color;


void main()
{

	light_color = vec4(1.0, 1.0, 1.0, 1.0);
	frag_color = light_color;
}