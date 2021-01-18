#version 330 core
//out value:
out vec4 fragment_color;

//in:
in vec4 vertex_color_to_fragment;

void main()
{
	fragment_color = vertex_color_to_fragment;
}