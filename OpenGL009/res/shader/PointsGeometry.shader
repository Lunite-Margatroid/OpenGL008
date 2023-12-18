#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 4)out;

in VS_OUT
{
	vec3 FColor;
}gs_in[];

out vec3 fColor;

void main()
{
	fColor = gs_in[0].FColor;
	gl_Position = gl_in[0].gl_Position + vec4(-0.2f, -0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.2f, -0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(-0.2f, 0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gl_in[0].gl_Position + vec4(0.2f, 0.2f, 0.0f, 0.0f);
	EmitVertex();
	EndPrimitive();
}