#version 330
out vec4 fragColor;
in vec2 v_uv;


in vec3 v_vertex;
in vec3 v_normal;

uniform sampler2D u_texture_night;
uniform sampler2D u_texture_spec;
uniform sampler2D u_texture_normal;
uniform sampler2D u_texture;

uniform vec3 u_light_dir;
uniform vec3 u_cam_pos;
uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;


void main(void){

	vec4 texture_color = texture(u_texture, v_uv);
	vec3 texture_normal = texture(u_texture_normal, v_uv).xyz;

	vec3 N = normalize(v_normal);
	vec3 L = normalize(u_light_dir - v_vertex);
	vec3 R = normalize(-reflect(L, N) );
	vec3 E = normalize(u_cam_pos - v_vertex);

	float NdotL = max ( dot (N,L) , 0.0 ) ;
	float RdotE = pow( max ( dot (R,E) , 0.0 ) , u_shininess ) ;

	// Blinn Specular

	vec3 H = normalize( L + E );
	float blinnSpecular = pow( max ( dot (N,H) , 0.0 ) , u_shininess ) ;
	

	vec3 final_color =  texture_color.xyz  * u_ambient + texture_color.xyz * u_diffuse * NdotL + texture_color.xyz * blinnSpecular * u_specular;

	// STEP 8: get the color from the texture
	fragColor = vec4 (final_color, 1.0);

}
