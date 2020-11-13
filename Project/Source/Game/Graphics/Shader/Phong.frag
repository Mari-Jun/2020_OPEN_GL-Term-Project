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

//Directional Light
struct DirectionalLight
{
	//Directional Light�� ����
	vec3 direction;
	//Diffuse Light�� ����
	vec3 diffuseColor;
	//Specular Light�� ����
	vec3 specularColor;
};

//Camera Pos
uniform vec3 uCameraPos;

//����ŧ�� �������� ����
uniform float uSpecBrightness;

//�ں��Ʈ ������
uniform vec3 uAmbientLight;

//Directional Light
uniform DirectionalLight uDirLight;

void main()
{
	//�����׸�Ʈ ������ ����ȭ
	vec3 N = normalize(fragNormal);

	//���� ����
	vec3 L = normalize(-uDirLight.direction);

	//ǥ�鿡�� ī�޶�� ���ϴ� ����
	vec3 V = normalize(uCameraPos - fragWorldPos);

	//������ �����׸�Ʈ�κ��� ƨ�� ������ ����
	vec3 R = normalize(reflect(-L, N));

	//�����׸�Ʈ ������ Directional Light�� ������� ����
	float NdotL = max(0.0, dot(N, L));

	//����Ʈ�� ���� ����
	vec3 diffuseLight = uDirLight.diffuseColor * fragColor * NdotL;

	//����ŧ�� ����Ʈ�� ����
	vec3 specularLight = uDirLight.diffuseColor * uDirLight.specularColor * pow(max(0.0, dot(R, V)), uSpecBrightness);

	//�ں��Ʈ ����Ʈ�� ����
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