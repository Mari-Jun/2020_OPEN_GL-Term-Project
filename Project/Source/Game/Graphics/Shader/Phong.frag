#version 330

//Vert���� ������ �͵�
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 fragWorldPos;

//��
out vec4 outColor;

//�ؽ���
uniform sampler2D uDiffuseTexture;

//����
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

//����ŧ�� �������� ����
uniform float uSpecBrightness;

//�ں��Ʈ ������
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

//Directional Light ���
vec3 calculDirLight(DirectionalLight light, vec3 N, vec3 V)
{
	//���� ����
	vec3 L = normalize(-light.direction);

	//������ �����׸�Ʈ�κ��� ƨ�� ������ ����
	vec3 R = normalize(reflect(-L, N));

	//�����׸�Ʈ ������ Directional Light�� ������� ����
	float NdotL = max(0.0, dot(N, L));

	//����Ʈ�� ���� ����
	vec3 diffuseLight = light.diffuseColor * fragColor * NdotL;

	//����ŧ�� ����Ʈ�� ����
	vec3 specularLight = light.diffuseColor * light.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	return diffuseLight + specularLight;
}

//Point Light ���
vec3 calculPointLight(PointLight light, vec3 pos, vec3 N, vec3 V)
{
	//���� ����
	vec3 L = normalize(light.position - pos);

	//������ �����׸�Ʈ�κ��� ƨ�� ������ ����
	vec3 R = normalize(reflect(-L, N));

	//���� ����� ����� ����
	float NdotL = max(0.0, dot(N, L));

	vec3 diffuseLight = light.diffuseColor * fragColor * NdotL;
	vec3 specularLight = light.diffuseColor * light.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	float dist = length(light.position - pos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));	

	diffuseLight *= attenuation;
	specularLight *= attenuation;

	return diffuseLight + specularLight;
}

//Spot Light ���
vec3 calculSpotLight(SpotLight light, vec3 pos, vec3 N, vec3 V)
{
	//���� ����
	vec3 L = normalize(light.position - pos);

	//������ �����׸�Ʈ�κ��� ƨ�� ������ ����
	vec3 R = normalize(reflect(-L, N));

	//���� ����� ����� ����
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
	//�����׸�Ʈ ������ ����ȭ
	vec3 N = normalize(fragNormal);

	//ǥ�鿡�� ī�޶�� ���ϴ� ����
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

	//�ں��Ʈ ����Ʈ�� ����
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
