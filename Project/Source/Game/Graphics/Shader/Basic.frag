#version 330

//Vert에서 가져온 것들
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragColor;
in vec3 fragWorldPos;

//색
out vec4 outColor;

//텍스쳐
uniform sampler2D uDiffuseTexture;

void main()
{
	vec4 texColor = texture(uDiffuseTexture, fragTexCoord);

	if(texColor.a < 0.1)
	{
		discard;
	}

	if(texColor.xyz == vec3(0.0,0.0,0.0))
	{
		outColor = vec4(fragColor, 1.0);
	}
	else
	{
		outColor = texColor * vec4(fragColor, 1.0);
	}
}
