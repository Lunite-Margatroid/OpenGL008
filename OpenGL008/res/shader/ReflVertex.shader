#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 modelTrans;
uniform mat4 viewTrans;
uniform mat4 projectionTrans;
uniform mat3 normalMat;
void main()
{
	FragPos = vec3(modelTrans * vec4(aPos, 1.0f));
	gl_Position = projectionTrans * viewTrans * modelTrans * vec4(aPos, 1.0f);
	Normal = normalMat * aNormal;
}