#version 330

//Vert에서 가져온 것들
in vec2 fragTexCoord;

//색
out vec4 outColor;

//텍스쳐
uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, fragTexCoord);
}
