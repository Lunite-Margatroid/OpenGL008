#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
out VS_OUT{
	vec3 FColor;
}vs_out;
void main()
{
	gl_Position = vec4(aPos, 0.0f, 1.0f);
	vs_out.FColor = aColor;
	gl_PointSize = 5.0f;
}