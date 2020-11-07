#version 330

//Vert���� ������ �͵�
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 fragWorldPos;

//��
out vec4 outColor;

//���߿� ���� �ؽ���
uniform sampler2D uTexture;

//Directional Light
struct DirectionalLight
{
	//Directional Light�� ����
	vec3 direction;
	//Light�� ����
	vec3 color;
};

//Camera Pos
uniform vec3 uCameraPos;

//Directional Light
uniform DirectionalLight uDirLight;

void main()
{
	//�����׸�Ʈ ������ ����ȭ
	vec3 normal = normalize(fragNormal);

	//ǥ�鿡�� ī�޶�� ���ϴ� ����
	vec3 toCamera = normalize(uCameraPos - fragWorldPos);

	//�����׸�Ʈ ������, ǥ�鿡�� ī�޶�� ���ϴ� ������ ������
	//1.0���� ���ִ� ���� ������ �����ϴ� ȿ��. �������� ���� ��� �޽��� �߽ɺΰ� �����
	float rimLight = 1.0 - max(0.0, dot(normal, toCamera));
	rimLight = pow(rimLight, 2);

	//�����׸�Ʈ ������ Directional Light�� ������� ����
	float lightAmt = max(0.0, dot(normal, uDirLight.direction));
	//����Ʈ�� ���� ����
	vec3 fragLight = uDirLight.color * lightAmt;

	//outColor = texture(uTexture, fragTexCoord);

	//�� ������Ʈ X
	//outColor = vec4(fragColor * fragLight, 1.0);
	//�� ������Ʈ �߰�
	outColor = vec4(fragColor * fragLight + rimLight, 1.0);
}
