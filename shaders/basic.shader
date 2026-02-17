#shader vertex
#version 330 core

in vec3 position;
in vec2 texCoord;

out vec3 worldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	worldPos = position;
}



#shader fragment
#version 330 core

in vec3 worldPos;

out vec4 color;

uniform float		u_blend;
uniform sampler2D	u_textureSampler;

void main()
{
	float variation = fract(float(gl_PrimitiveID) * 0.618033988749895);
	float brightness = 0.7 + variation * 0.6;

	vec3 tmp_color = vec3(0.5, 0.5, 0.5) * brightness;
	tmp_color = clamp(tmp_color, 0.0, 1.0);
	vec4 grey_color = vec4(tmp_color, 0.0);

	vec2 uv = worldPos.zy;
	vec4 texture_color = texture(u_textureSampler, uv);

	color = mix(grey_color, texture_color, u_blend);

}
