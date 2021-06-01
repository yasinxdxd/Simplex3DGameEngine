#version 330 core
out vec4 fragment_color;

in vec3 texture_direction;

uniform samplerCube cube_map;

void main()
{
	fragment_color = texture(cube_map, texture_direction);
}