#version 330 core

struct Material
{
	vec4 baseColor;
};


in vec2 TexCoord;
out vec4 fragColor;

uniform Material material;
uniform sampler2D sprite;

void main()
{
	vec4 diffuse = texture(sprite, TexCoord);
	vec4 result = diffuse * material.baseColor;

	float alpha = texture(sprite, TexCoord).r;
	alpha *= material.baseColor.w;

    fragColor = vec4(result.xyz, alpha);
} 