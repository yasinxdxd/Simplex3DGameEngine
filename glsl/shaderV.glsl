#version 330 core

//layouts:
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec4 vertex_color;

//outs:
out vec4 vertex_color_to_fragment;
out vec3 vertex_normal_to_fragment;
out vec3 fragment_position;
//uniforms:
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	vertex_color_to_fragment = vertex_color;
	vertex_normal_to_fragment = vertex_normal;
	fragment_position = vec3(model * vec4(vertex_position, 1.0));


	gl_Position = projection * view * vec4(fragment_position, 1.0);
} 