#version 330

//위치 벡터, 노멀 벡터, 텍스쳐 좌표, 색깔
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform vec3 uColor;

//월드변환, 뷰변환
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;


out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragColor;

//프래그먼트의 월드 공간 위치
out vec3 fragWorldPos;

void main()
{
	//위치를 동차좌표로 변환
	vec4 pos = vec4(inPosition, 1.0);

	//위치를 월드 공간으로 변환
	pos = pos * uWorldTransform;

	//버텍스의 위치는 프래그먼트의 위치임
	fragWorldPos = pos.xyz;

	//클립 공간으로 변환
	gl_Position = pos * uViewProj;

	//법선을 월드 공간으로 변환
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	//텍스쳐 좌표 전달
	fragTexCoord = inTexCoord;

	//컬러 전달
	fragColor = uColor;
}