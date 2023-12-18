#version 330 core
layout(location = 0) in vec3 aPos;
out vec3 TexDirection;

uniform mat4 projectionTrans;
uniform mat4 viewTrans;

void main()
{
	vec4 temp = projectionTrans * viewTrans * vec4(aPos, 1.0f);
	gl_Position = temp.syww;	// ��z��������w���� ʹ�����Զ����1.0 ����Զ���
	TexDirection = aPos;
}