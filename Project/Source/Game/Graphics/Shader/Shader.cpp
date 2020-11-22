#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader()
	: mVertexShader(0)
	, mFragmentShader(0)
	, mShaderProgram(0)
{

}

Shader::~Shader()
{

}

bool Shader::load(const std::string& vertName, const std::string& fragName)
{
	//Compile Shader
	if (!compileShader(vertName,GL_VERTEX_SHADER,mVertexShader) || 
		!compileShader(fragName, GL_FRAGMENT_SHADER, mFragmentShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

	//Complete Shader?
	if (!isLinked())
	{
		return false;
	}

	return true;	
}

void Shader::unLoad()
{
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mShaderProgram);
}

void Shader::setActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::setMatrixUniform(const char* name, const Matrix4& matrix)
{
	GLint location = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

void Shader::SetVectorUniform(const char* name, const Vector3& vector)
{
	GLint location = glGetUniformLocation(mShaderProgram, name);
	glUniform3fv(location, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char* name, float value)
{
	GLint location = glGetUniformLocation(mShaderProgram, name);
	glUniform1f(location, value);
}

void Shader::SetIntUniform(const char* name, int value)
{
	GLint location = glGetUniformLocation(mShaderProgram, name);
	glUniform1i(location, value);
}

bool Shader::compileShader(const std::string& fileName, GLenum shaderType, GLint& shader)
{
	//Open shader file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		std::stringstream ss;
		ss << shaderFile.rdbuf();
		std::string contents = ss.str();
		const char* contentsChar = contents.c_str();

		shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &contentsChar, nullptr);
		glCompileShader(shader);

		if (!isCompiled(shader))
		{
			std::cerr << "Error : Failed to compile shader " << fileName << '\n';
			return false;
		}
	}
	else
	{
		std::cerr << "Shader file not found : " << fileName << '\n';
		return false;
	}
	return true;
}

bool Shader::isCompiled(GLint shader)
{
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, errorLog);
		std::cerr << "Compile Error : " << errorLog << '\n';
		return false;
	}
	return true;
}

bool Shader::isLinked()
{
	GLint result;
	glGetShaderiv(mShaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		GLchar errorLog[512];
		glGetProgramInfoLog(mShaderProgram, 512, nullptr, errorLog);
		std::cerr << "Link Error : " << errorLog << '\n';
		return false;
	}
	return true;
}