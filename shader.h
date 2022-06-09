#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader();
	~Shader();

	void load(const char* vertexPath, const char* fragmentPath);
	void Use();
	void Cleanup();

	void SetUniform(const char* name, float value);
	void SetUniform(const char* name, int value);

	unsigned int GetProgram();
private:
	unsigned int m_program;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
};

#endif // SHADER_H
