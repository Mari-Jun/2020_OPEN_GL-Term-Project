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
uniform sampler2D uNormalTexture;
uniform sampler2D uSpecularTexture;

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
	vec3 normal = normalize(fragNormal);

	//ǥ�鿡�� ī�޶�� ���ϴ� ����
	vec3 toCamera = normalize(uCameraPos - fragWorldPos);

	//������ �����׸�Ʈ�κ��� ƨ�� ������ ����
	//vec3 refl = reflect(-uDirLight.direction, normal);

	vec3 halfVec = normalize(toCamera + uDirLight.direction);

	//�����׸�Ʈ ������, ǥ�鿡�� ī�޶�� ���ϴ� ������ ������
	//1.0���� ���ִ� ���� ������ �����ϴ� ȿ��. �������� ���� ��� �޽��� �߽ɺΰ� �����
	float rimLight = 1.0 - max(0.0, dot(normal, toCamera));
	rimLight = pow(rimLight, 2);

	//�����׸�Ʈ ������ Directional Light�� ������� ����
	float lightAmt = max(0.0, dot(normal, uDirLight.direction));

	//����Ʈ�� ���� ����
	vec3 fragLight = uDirLight.diffuseColor * lightAmt;
	vec3 diffuseLight = fragColor * fragLight + rimLight;
	//vec3 diffuseLight = texture(uDiffuseTexture, fragTexCoord).xyz * fragLight + rimLight;

	//����ŧ�� ����Ʈ�� ����
	//float specBright = pow(max(0.0, dot(refl, toCamera)), uSpecBrightness);
	float specBright = pow(max(0.0, dot(halfVec, normal)), uSpecBrightness);
	vec3 specularLight = uDirLight.specularColor * uDirLight.diffuseColor * specBright;
	//vec3 specularLight = texture(uSpecularTexture, fragTexCoord).x * uDirLight.diffuseColor * specBright;

	//�ں��Ʈ ����Ʈ�� ����
	vec3 ambientLight = uAmbientLight * fragColor;

	vec3 Phong = ambientLight;

	//outColor = texture(uDiffuseTexture, fragTexCoord) + vec4(Phong, 1.0);
	outColor = vec4(Phong, 1.0);
}