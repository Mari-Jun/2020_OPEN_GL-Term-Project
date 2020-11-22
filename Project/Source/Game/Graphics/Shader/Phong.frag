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

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PointLight
{
	vec3 position;
	vec3 diffuseColor;
	vec3 specularColor;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 diffuseColor;
	vec3 specularColor;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outCutOff;
};

//Camera Pos
uniform vec3 uCameraPos;

//스펙큘러 라이팅의 세기
uniform float uSpecBrightness;

//앰비언트 라이팅
uniform vec3 uAmbientLight;

#define NUM_DIR_LIGHTS 10
#define NUM_POINT_LIGHTS 10
#define NUM_SPOT_LIGHTS 10

//Directional Light
uniform DirectionalLight uDirLight[NUM_DIR_LIGHTS];
uniform int uDirSize;
//Point Light
uniform PointLight uPointLight[NUM_POINT_LIGHTS];
uniform int uPointSize;
//Spot Light
uniform SpotLight uSpotLight[NUM_SPOT_LIGHTS];
uniform int uSpotSize;

//Directional Light 계산
vec3 calculDirLight(DirectionalLight light, vec3 N, vec3 V)
{
	//광원 방향
	vec3 L = normalize(-light.direction);

	//광선이 프래그먼트로부터 튕겨 나오는 벡터
	vec3 R = normalize(reflect(-L, N));

	//프래그먼트 법선과 Directional Light의 방향과의 내적
	float NdotL = max(0.0, dot(N, L));

	//라이트의 양을 결정
	vec3 diffuseLight = light.diffuseColor * fragColor * NdotL;

	//스펙큘러 라이트를 구함
	vec3 specularLight = light.diffuseColor * light.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	return diffuseLight + specularLight;
}

//Point Light 계산
vec3 calculPointLight(PointLight light, vec3 pos, vec3 N, vec3 V)
{
	//광원 방향
	vec3 L = normalize(light.position - pos);

	//광선이 프래그먼트로부터 튕겨 나오는 벡터
	vec3 R = normalize(reflect(-L, N));

	//광원 방향과 노멀의 내적
	float NdotL = max(0.0, dot(N, L));

	vec3 diffuseLight = light.diffuseColor * fragColor * NdotL;
	vec3 specularLight = light.diffuseColor * light.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	float dist = length(light.position - pos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	

	diffuseLight *= attenuation;
	specularLight *= attenuation;

	return diffuseLight + specularLight;
}

//Spot Light 계산
vec3 calculSpotLight(SpotLight light, vec3 pos, vec3 N, vec3 V)
{
	//광원 방향
	vec3 L = normalize(light.position - pos);

	//광선이 프래그먼트로부터 튕겨 나오는 벡터
	vec3 R = normalize(reflect(-L, N));

	//광원 방향과 노멀의 내적
	float NdotL = max(0.0, dot(N, L));

	vec3 diffuseLight = light.diffuseColor * fragColor * NdotL;
	vec3 specularLight = light.diffuseColor * light.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	float dist = length(light.position - pos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	

	float angle = dot(light.direction, -L);
	float epsilon = light.cutOff - light.outCutOff;
	float intensity = clamp((angle-light.outCutOff)/epsilon, 0.0, 1.0);

	diffuseLight *= attenuation * intensity;
	specularLight *= attenuation * intensity;

	return diffuseLight + specularLight;
}

void main()
{
	//프래그먼트 법선의 정규화
	vec3 N = normalize(fragNormal);

	//표면에서 카메라로 향하는 벡터
	vec3 V = normalize(uCameraPos - fragWorldPos);

	vec3 finalLight;
	for(int i = 0; i < uDirSize; ++i)
	{
		finalLight += calculDirLight(uDirLight[i], N, V);
	}

	for(int i = 0; i < uPointSize; ++i)
	{
		finalLight += calculPointLight(uPointLight[i], fragWorldPos, N, V);
	}

	for(int i = 0; i< uSpotSize; ++i)
	{
		finalLight += calculSpotLight(uSpotLight[i], fragWorldPos, N, V);
	}

	//앰비언트 라이트를 구함
	vec3 ambientLight = uAmbientLight * fragColor;

	vec3 Phong = finalLight + ambientLight;
	
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
