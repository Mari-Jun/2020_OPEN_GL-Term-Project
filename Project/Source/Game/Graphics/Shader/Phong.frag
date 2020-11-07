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
uniform sampler2D uNormalTexture;
uniform sampler2D uSpecularTexture;

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
	vec3 normal = normalize(fragNormal);

	//표면에서 카메라로 향하는 벡터
	vec3 toCamera = normalize(uCameraPos - fragWorldPos);

	//광선이 프래그먼트로부터 튕겨 나오는 벡터
	//vec3 refl = reflect(-uDirLight.direction, normal);

	vec3 halfVec = normalize(toCamera + uDirLight.direction);

	//프래그먼트 법선과 Directional Light의 방향과의 내적
	float lightAmt = max(0.0, dot(normal, uDirLight.direction));

	//라이트의 양을 결정
	vec3 fragLight = uDirLight.diffuseColor * lightAmt;
	vec3 diffuseLight = fragColor * fragLight;
	//vec3 diffuseLight = texture(uDiffuseTexture, fragTexCoord).xyz * fragLight;

	//스펙큘러 라이트를 구함
	//float specBright = pow(max(0.0, dot(refl, toCamera)), uSpecBrightness);
	float specBright = pow(max(0.0, dot(halfVec, normal)), uSpecBrightness);
	vec3 specularLight = uDirLight.specularColor * uDirLight.diffuseColor * specBright;
	//vec3 specularLight = texture(uSpecularTexture, fragTexCoord).x * uDirLight.diffuseColor * specBright;

	//앰비언트 라이트를 구함
	vec3 ambientLight = uAmbientLight * fragColor;

	vec3 Phong = diffuseLight + specularLight + ambientLight;

	outColor = texture(uDiffuseTexture, fragTexCoord) + vec4(Phong, 1.0);
	//outColor = vec4(Phong, 1.0);
}