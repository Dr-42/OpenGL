#include "shader.h"

#include <iostream>

Shader::Shader()
{
	m_program = 0;
	m_vertexShader = 0;
	m_fragmentShader = 0;
}

Shader::~Shader()
{
	if (m_vertexShader)
		glDeleteShader(m_vertexShader);
	if (m_fragmentShader)
		glDeleteShader(m_fragmentShader);
	if (m_program)
		glDeleteProgram(m_program);
}

void Shader::load(const char* vertexPath, const char* fragmentPath)
{
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	vShaderFile.open(vertexPath);
	std::stringstream vShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	vShaderFile.close();

	std::ifstream fShaderFile;
	fShaderFile.open(fragmentPath);
	std::stringstream fShaderStream;
	fShaderStream << fShaderFile.rdbuf();
	fShaderFile.close();

	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();	

	glShaderSource(m_vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(m_fragmentShader, 1, &fShaderCode, NULL);

	glCompileShader(m_vertexShader);
	glCompileShader(m_fragmentShader);

	// Check for errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::Cleanup(){
	glDeleteProgram(m_program);
}

void Shader::SetUniform(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::SetUniform(const char *name, double value){
	glUniform1d(glGetUniformLocation(m_program, name), value);
}

unsigned int Shader::GetProgram()
{
	return m_program;
}
