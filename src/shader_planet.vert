#version 330
 
in vec3 a_vertex;
in vec2 a_uv;
in vec3 a_normal;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_vertex;
out vec3 v_color;

void main()
{
	gl_Position = u_projection * u_model * vec4(a_vertex,1.0);

	v_vertex = (u_model * vec4( a_vertex , 1.0 )).xyz;
	v_normal = a_normal;
	v_uv = a_uv;

}