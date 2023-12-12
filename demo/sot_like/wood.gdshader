/*
	木目シェーダー by あるる（きのもと 結衣）
	Grain Shader by Yui Kinomoto @arlez80

	MIT License
*/
shader_type spatial;
// render_mode;

uniform vec4 light_color = vec4( 0.9529411764705882, 0.8588235294117647, 0.7490196078431373, 1.0 );
uniform vec4 dark_color = vec4( 0.7490196078431373, 0.6196078431372549, 0.49019607843137253, 1.0 );

uniform float ring_scale = 4.4;
uniform float wave_scale = 8.454;
uniform float random_scale = 4.6;
uniform float noise_scale = 0.03;

vec2 random( vec2 pos )
{ 
	return fract(
		sin(
			vec2(
				dot(pos, vec2(12.9898,78.233))
			,	dot(pos, vec2(-148.998,-65.233))
			)
		) * 43758.5453
	);
}

float value_noise( vec2 pos )
{
	vec2 p = floor( pos );
	vec2 f = fract( pos );

	float v00 = random( p + vec2( 0.0, 0.0 ) ).x;
	float v10 = random( p + vec2( 1.0, 0.0 ) ).x;
	float v01 = random( p + vec2( 0.0, 1.0 ) ).x;
	float v11 = random( p + vec2( 1.0, 1.0 ) ).x;

	vec2 u = f * f * ( 3.0 - 2.0 * f );

	return mix( mix( v00, v10, u.x ), mix( v01, v11, u.x ), u.y );
}

void fragment( )
{
	vec2 shift_uv = UV;
	shift_uv.x += value_noise( UV * random_scale );
	float x = shift_uv.x + sin( shift_uv.y * wave_scale );
	float f = mod( x * ring_scale + random( UV ).x * noise_scale, 1.0 );

	ALBEDO = mix( light_color, dark_color, f ).rgb;
	ALPHA = mix( light_color, dark_color, f ).a;
}
