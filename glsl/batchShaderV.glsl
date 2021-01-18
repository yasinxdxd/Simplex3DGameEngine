#version 330 core

//layouts:
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec4 vertex_color;
layout(location = 4) in float textureID;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertex_color_to_fragment;

void main()
{
	gl_Position = model * vec4(vertex_position, 1.0);
	//projection* view* model*
}