#version 330
out vec4 fragColor;
in vec2 v_uv;

uniform vec3 u_color;
uniform sampler2D u_texture;

void main(void){


	vec4 texture_color = texture(u_texture, v_uv);

	vec3 final_color = texture(u_texture, v_uv).xyz;

	fragColor = vec4 (final_color, 1.0);
}
