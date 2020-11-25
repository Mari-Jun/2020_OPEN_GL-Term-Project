#version 330

//��ġ ����, ��� ����, �ؽ��� ��ǥ, ����
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;
layout (location = 3) in vec3 inAmbientColor;
layout (location = 4) in vec3 inDiffuseColor;
layout (location = 5) in vec3 inSpecularColor;

uniform vec3 uColor;
uniform vec3 uTexSize;
uniform mat4 uInvertView;

//���庯ȯ, �亯ȯ
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragAColor;
out vec3 fragDColor;
out vec3 fragSColor;

//�����׸�Ʈ�� ���� ���� ��ġ
out vec3 fragWorldPos;

void main()
{
	//��ġ�� ������ǥ�� ��ȯ
	//vec4 pos = vec4(inPosition.x * uTexSize.x, inPosition.y * uTexSize.y, inPosition.z, 1.0);
	vec4 pos = vec4(inPosition * uTexSize, 1.0);

	//��ġ�� ���� �������� ��ȯ
	pos = pos * uInvertView * uWorldTransform;

	//���ؽ��� ��ġ�� �����׸�Ʈ�� ��ġ��
	fragWorldPos = pos.xyz;

	//Ŭ�� �������� ��ȯ
	gl_Position = pos * uViewProj;

	//������ ���� �������� ��ȯ
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	//�ؽ��� ��ǥ ����
	fragTexCoord = inTexCoord;

	//�÷� ����
	fragAColor = uColor;
	fragDColor = uColor;
}