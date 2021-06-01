#version 330 core

layout(location = 0) in vec3 vertex_position;

out vec3 texture_direction;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	texture_direction = vertex_position;
	gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}