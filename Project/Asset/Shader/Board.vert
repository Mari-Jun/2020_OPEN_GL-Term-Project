#version 330

//위치 벡터, 노멀 벡터, 텍스쳐 좌표, 색깔
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;
layout (location = 3) in vec3 inAmbientColor;
layout (location = 4) in vec3 inDiffuseColor;
layout (location = 5) in vec3 inSpecularColor;

uniform vec3 uColor;
uniform vec3 uTexSize;
uniform mat4 uInvertView;

//월드변환, 뷰변환
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragAColor;
out vec3 fragDColor;
out vec3 fragSColor;

//프래그먼트의 월드 공간 위치
out vec3 fragWorldPos;

void main()
{
	//위치를 동차좌표로 변환
	//vec4 pos = vec4(inPosition.x * uTexSize.x, inPosition.y * uTexSize.y, inPosition.z, 1.0);
	vec4 pos = vec4(inPosition * uTexSize, 1.0);

	//위치를 월드 공간으로 변환
	pos = pos * uInvertView * uWorldTransform;

	//버텍스의 위치는 프래그먼트의 위치임
	fragWorldPos = pos.xyz;

	//클립 공간으로 변환
	gl_Position = pos * uViewProj;

	//법선을 월드 공간으로 변환
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	//텍스쳐 좌표 전달
	fragTexCoord = inTexCoord;

	//컬러 전달
	fragAColor = uColor;
	fragDColor = uColor;
}