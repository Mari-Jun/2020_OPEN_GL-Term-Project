#version 330

//위치 벡터, 노멀 벡터, 텍스쳐 좌표, 색깔
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;
layout (location = 3) in vec3 inAmbientColor;
layout (location = 4) in vec3 inDiffuseColor;
layout (location = 5) in vec3 inSpecularColor;

uniform vec3 uColor;

//월드변환, 뷰변환
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 fragTexCoord;

void main()
{
	//위치를 동차좌표로 변환
	vec4 pos = vec4(inPosition, 1.0);

	//월드 공간 -> 클립 공간으로 변환
	gl_Position = pos * uWorldTransform * uViewProj;

	//텍스쳐 좌표 전달
	fragTexCoord = inTexCoord;
}