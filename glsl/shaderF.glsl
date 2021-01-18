#version 330 core
//out value:
out vec4 fragment_color;


//coming from vertex shader
in vec4 vertex_color_to_fragment;
in vec3 vertex_normal_to_fragment;
in vec3 model_vertex_position;
//coming from light fragment
vec4 light_color = vec4(1,0.96,0.89,1);
//uniforms
uniform vec3 light_position;
uniform vec3 view_position;
uniform vec4 fast_color;



void main()
{
	//ambient
	float ambient_strength = 0.3;
	vec4 ambient = ambient_strength * light_color;
	//diffuse
	vec3 light_direction = normalize(light_position - model_vertex_position);
	vec3 norm = normalize(vertex_normal_to_fragment);
	float diff = max(0.0, dot(norm, light_direction));
	vec4 diffuse = diff * light_color;
	//specular
	float specular_strength = 0.5;
	vec3 view_direction = normalize(view_position - model_vertex_position);
	vec3 reflect_direction = reflect(norm, -light_direction);
	float spec = pow(max(0.0, dot(view_direction, reflect_direction)), 2);
	vec4 specular = specular_strength * spec * light_color;


	vec4 result = (ambient + diffuse + specular) * fast_color;

	//vertex_color_to_fragment---> colors coming from all vertices.
	//fast_color---> one color on all model.

	fragment_color = result;
}