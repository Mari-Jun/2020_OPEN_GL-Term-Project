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

void main()
{
	if(texture(uDiffuseTexture, fragTexCoord).xyz == 0)
	{
		outColor = vec4(fragColor, 1.0);
	}
	else
	{
		outColor = texture(uDiffuseTexture, fragTexCoord) * vec4(fragColor, 1.0);
	}
}
