#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 projectionTrans;
uniform mat4 viewTrans;
uniform mat4 modelTrans;

void main()
{
	gl_Position = projectionTrans * viewTrans * modelTrans * vec4(aPos, 1.0f);
	texCoord = aTexCoord;
}