#version 330

//Vert���� ������ �͵�
in vec2 fragTexCoord;

//��
out vec4 outColor;

//�ؽ���
uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, fragTexCoord);
}
