#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform samplerCube cubeTex;
uniform vec3 viewPos;

void main()
{
	vec3 viewDir = normalize(FragPos-viewPos);
	vec3 sampleDir = reflect(viewDir, Normal);
	FragColor = vec4(texture(cubeTex, sampleDir).rgb, 1.0f);
}