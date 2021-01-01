#version 330 core
//out value:
out vec4 fragment_color;


//coming from vertex shader
in vec4 vertex_color_to_fragment;
in vec3 vertex_normal_to_fragment;
in vec3 fragment_position;
//coming from light fragment
vec4 light_color = vec4(1,1,1,1);
//uniforms
uniform vec3 light_position;





void main()
{
	//ambient
	float ambient_strength = 0.1;
	vec4 ambient = ambient_strength * light_color;
	//diffuse
	vec3 light_direction = normalize(light_position - fragment_position);
	float diff = max(dot(normalize(vertex_normal_to_fragment), light_direction), 0.0);
	vec4 diffuse = diff * light_color;

	vec3 result = (ambient.xyz + diffuse.xyz) * vertex_color_to_fragment.xyz;

	fragment_color = vec4(result, 1.0);
}