#version 330

in vec2 fragTexCoord;
in vec3 fragColor;
out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	//outColor = texture(uTexture, fragTexCoord);
	outColor = vec4(fragColor, 1.0);
}
