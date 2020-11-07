#version 330

layout (location = 0) in vec3 inPos;

uniform vec3 uColor;

out vec3 passColor;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

void main()
{
	vec4 pos = vec4(inPos, 1.0);
	gl_Position = pos * uWorldTransform * uViewProj;
	passColor = uColor;
}