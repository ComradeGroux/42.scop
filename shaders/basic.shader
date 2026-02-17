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

uniform int			textured;
uniform sampler2D	textureSampler;

void main()
{
	if (textured == 0)
	{
		float variation = fract(float(gl_PrimitiveID) * 0.618033988749895);
		float brightness = 0.7 + variation * 0.6;

		vec3 finalColor = vec3(0.5, 0.5, 0.5) * brightness;

		finalColor = clamp(finalColor, 0.0, 1.0);

		color = vec4(finalColor, 1.0);
	}
	else
	{
		vec2 uv = worldPos.zy;
		color = texture(textureSampler, uv);
	}
}
