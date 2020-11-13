#version 330

//Vert에서 가져온 것들
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 fragWorldPos;

//색
out vec4 outColor;

//텍스쳐
uniform sampler2D uDiffuseTexture;

//알파
uniform float uAlpha = 1.0f;

//Directional Light
struct DirectionalLight
{
	//Directional Light의 방향
	vec3 direction;
	//Diffuse Light의 색상
	vec3 diffuseColor;
	//Specular Light의 색상
	vec3 specularColor;
};

//Camera Pos
uniform vec3 uCameraPos;

//스펙큘러 라이팅의 세기
uniform float uSpecBrightness;

//앰비언트 라이팅
uniform vec3 uAmbientLight;

//Directional Light
uniform DirectionalLight uDirLight;

void main()
{
	//프래그먼트 법선의 정규화
	vec3 N = normalize(fragNormal);

	//광원 방향
	vec3 L = normalize(-uDirLight.direction);

	//표면에서 카메라로 향하는 벡터
	vec3 V = normalize(uCameraPos - fragWorldPos);

	//광선이 프래그먼트로부터 튕겨 나오는 벡터
	vec3 R = normalize(reflect(-L, N));

	//프래그먼트 법선과 Directional Light의 방향과의 내적
	float NdotL = max(0.0, dot(N, L));

	//라이트의 양을 결정
	vec3 diffuseLight = uDirLight.diffuseColor * fragColor * NdotL;

	//스펙큘러 라이트를 구함
	vec3 specularLight = uDirLight.diffuseColor * uDirLight.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	//앰비언트 라이트를 구함
	vec3 ambientLight = uAmbientLight * fragColor;

	vec3 Phong = diffuseLight + specularLight + ambientLight;
	
	vec4 texColor = texture(uDiffuseTexture, fragTexCoord);

	if(texColor.a < 0.1)
	{
		discard;
	}

	if(texColor.xyz == vec3(0.0,0.0,0.0))
	{
		outColor = vec4(Phong, uAlpha);
	}
	else
	{
		outColor = texColor * vec4(Phong, uAlpha);
	}
	
}