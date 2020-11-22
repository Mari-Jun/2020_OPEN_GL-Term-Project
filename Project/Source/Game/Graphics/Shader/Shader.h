#pragma once
#include <gl/glew.h>
#include <string>
#include "../../Math/Math.h"

class Shader final
{
public:
	Shader();
	~Shader();

	bool load(const std::string& vertName, const std::string& fragName);
	void unLoad();

	void setActive();

	//Set Matrix, Vector, Float Uniform ³ªÁß¿¡
	void setMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetFloatUniform(const char* name, float value);
	void SetIntUniform(const char* name, int value);

private:
	bool compileShader(const std::string& fileName, GLenum shaderType, GLint& shader);
	bool isCompiled(GLint shader);
	bool isLinked();

private:
	GLint mVertexShader;
	GLint mFragmentShader;
	GLint mShaderProgram;
};
