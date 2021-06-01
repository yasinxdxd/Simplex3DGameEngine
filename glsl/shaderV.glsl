#version 330 core

//layouts:
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;
layout(location = 3) in vec4 vertex_color;

//outs:
out vec4 vertex_color_to_fragment;
out vec2 vertex_texcoord_to_fragment;
out vec3 vertex_normal_to_fragment;
out vec3 model_vertex_position;
//uniforms:
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	vertex_color_to_fragment = vertex_color;
	vertex_texcoord_to_fragment = vertex_texcoord;
	//vertex_normal_to_fragment = vertex_normal; // with translate values
	vertex_normal_to_fragment = mat3(transpose(inverse(model))) * vertex_normal; //get rid of translate values
	model_vertex_position = vec3(model * vec4(vertex_position, 1.0));


	gl_Position = projection * view * model * vec4(vertex_position, 1.0); //    + vertex_normal*0.004
} 