shader_type spatial;
render_mode specular_schlick_ggx, unshaded, cull_back;//

uniform vec4 tint_color = vec4( 0.3, 0.4, 0.45, 1.0);
uniform sampler2D caustics;
uniform float slowdown : hint_range( 0.1, 10.0, 0.1 ) = 5.0;
uniform float time_caust : hint_range( 0.01, 1.0, 0.01 ) = 0.13;
uniform float caust_form : hint_range( 0.01, 1.0, 0.01 ) = 0.15;
uniform float tile: hint_range( 0.1, 16.0, 0.1 ) = 4.0;

void fragment() {

// Caustics
	float caustics_form = texture(caustics , UV * (tile + sin(TIME / slowdown) * time_caust )).r;//
	vec2 caustics_uv =  UV * (tile + cos(TIME / slowdown) * time_caust ) + caustics_form * caust_form ;
	float caustics_final = texture(caustics, caustics_uv).r;
	ALBEDO = (1.0-SCREEN_UV.y) * caustics_final * tint_color.rgb ;
	ALPHA = min(SCREEN_UV.y + 0.5, 1.0 ) * tint_color.a;
		
}