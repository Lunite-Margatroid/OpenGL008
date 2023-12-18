#version 330 core
in vec3 TexDirection;

uniform samplerCube cubeTex;

out vec4 FragColor;
void main()
{
	FragColor = vec4(texture(cubeTex, TexDirection));
}