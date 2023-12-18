#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out VS_OUT{
	vec3 FColor;
}vs_out;

layout(std140) uniform offsets
{
	vec4 offset[50];
};

void main()
{
	vec2 temp = vec2(0.0f, 0.f);
	if(gl_InstanceID%2 == 1)
		temp = aPos + offset[gl_InstanceID / 2].zw;
	else
		temp = aPos + offset[gl_InstanceID / 2].xy;
	gl_Position = vec4(temp, 0.0f, 1.0f);
	vs_out.FColor = aColor;
	gl_PointSize = 5.0f;
}