#version 330

//Vert에서 가져온 것들
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 fragWorldPos;

//색
out vec4 outColor;

//나중에 쓰일 텍스쳐
uniform sampler2D uTexture;

//Directional Light
struct DirectionalLight
{
	//Directional Light의 방향
	vec3 direction;
	//Light의 색상
	vec3 color;
};

//Camera Pos
uniform vec3 uCameraPos;

//Directional Light
uniform DirectionalLight uDirLight;

void main()
{
	//프래그먼트 법선의 정규화
	vec3 normal = normalize(fragNormal);

	//표면에서 카메라로 향하는 벡터
	vec3 toCamera = normalize(uCameraPos - fragWorldPos);

	//프래그먼트 법선과, 표면에서 카메라고 향하는 벡터의 내적값
	//1.0에서 빼주는 것은 내적을 반전하는 효과. 반전하지 않을 경우 메쉬의 중심부가 밝아짐
	float rimLight = 1.0 - max(0.0, dot(normal, toCamera));
	rimLight = pow(rimLight, 2);

	//프래그먼트 법선과 Directional Light의 방향과의 내적
	float lightAmt = max(0.0, dot(normal, uDirLight.direction));
	//라이트의 양을 결정
	vec3 fragLight = uDirLight.color * lightAmt;

	//outColor = texture(uTexture, fragTexCoord);

	//색 림라이트 X
	//outColor = vec4(fragColor * fragLight, 1.0);
	//색 림라이트 추가
	outColor = vec4(fragColor * fragLight + rimLight, 1.0);
}
