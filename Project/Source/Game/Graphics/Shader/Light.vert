#version 330

//��ġ ����, ��� ����, �ؽ��� ��ǥ, ����
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform vec3 uColor;

//���庯ȯ, �亯ȯ
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;


out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragColor;

//�����׸�Ʈ�� ���� ���� ��ġ
out vec3 fragWorldPos;

void main()
{
	//��ġ�� ������ǥ�� ��ȯ
	vec4 pos = vec4(inPosition, 1.0);

	//��ġ�� ���� �������� ��ȯ
	pos = pos * uWorldTransform;

	//���ؽ��� ��ġ�� �����׸�Ʈ�� ��ġ��
	fragWorldPos = pos.xyz;

	//Ŭ�� �������� ��ȯ
	gl_Position = pos * uViewProj;

	//������ ���� �������� ��ȯ
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	//�ؽ��� ��ǥ ����
	fragTexCoord = inTexCoord;

	//�÷� ����
	fragColor = uColor;
}