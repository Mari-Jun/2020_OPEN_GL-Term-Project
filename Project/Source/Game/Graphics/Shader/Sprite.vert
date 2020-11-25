#version 330

//��ġ ����, ��� ����, �ؽ��� ��ǥ, ����
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;
layout (location = 3) in vec3 inAmbientColor;
layout (location = 4) in vec3 inDiffuseColor;
layout (location = 5) in vec3 inSpecularColor;

uniform vec3 uColor;

//���庯ȯ, �亯ȯ
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 fragTexCoord;

void main()
{
	//��ġ�� ������ǥ�� ��ȯ
	vec4 pos = vec4(inPosition, 1.0);

	//���� ���� -> Ŭ�� �������� ��ȯ
	gl_Position = pos * uWorldTransform * uViewProj;

	//�ؽ��� ��ǥ ����
	fragTexCoord = inTexCoord;
}