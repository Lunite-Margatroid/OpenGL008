#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 TexDirection;

uniform mat4 projectionTrans;
uniform mat4 viewTrans;

void main()
{
	vec4 temp = projectionTrans * viewTrans * vec4(aPos, 1.0f);
	gl_Position = temp.syww;	// 让z分量等于w分量 使深度永远等于1.0 即最远深度
	TexDirection = aPos;
}