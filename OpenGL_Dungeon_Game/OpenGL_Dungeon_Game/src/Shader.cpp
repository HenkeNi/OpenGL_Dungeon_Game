#include "Shader.h"
#include <iostream>

Shader& Shader::use()
{
	glUseProgram(m_id);
	return *this;
}

void Shader::compile(const char* vertSrc, const char* fragSrc, const char* geoSrc)
{
	unsigned int sVertex, sFragment, gShader;

	sVertex = compileShader(vertSrc, GL_VERTEX_SHADER); // vertex shader
	sFragment = compileShader(fragSrc, GL_FRAGMENT_SHADER); // fragment shader
	 
	if (geoSrc != nullptr)
		gShader = compileShader(geoSrc, GL_GEOMETRY_SHADER); // geometry shader (optional)

	// shader program
	m_id = glCreateProgram();
	glAttachShader(m_id, sVertex);
	glAttachShader(m_id, sFragment);

	if (geoSrc != nullptr)
		glAttachShader(m_id, gShader);

	glLinkProgram(m_id);
	checkCompileErrors(m_id, "PROGRAM");

	// delete shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

	if (geoSrc != nullptr)
		glDeleteShader(gShader);
}

unsigned int Shader::compileShader(const char* src, unsigned int type)
{
	unsigned int shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &src, nullptr);
	glCompileShader(shaderId);

	auto t = type == GL_VERTEX_SHADER ? "VERETX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "GEOMETRY";
	checkCompileErrors(shaderId, t);

	return shaderId;
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];

	type == "PROGRAM" ? glGetProgramiv(object, GL_LINK_STATUS, &success) : glGetShaderiv(object, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		type == "PROGRAM" ? glGetProgramInfoLog(object, 1024, nullptr, infoLog) : glGetShaderInfoLog(object, 1024, nullptr, infoLog);
		std::cout << "ERROR::SHADER: " << (type == "PROGRAM" ? "Compile" : "Link") 
			<< "-time error: Type " << type << '\n' << infoLog << "\n ---------------------------------------------------- \n";
	}

}

void Shader::setFloat(const char* name, float value, bool useShader)
{
	if (useShader) use();
	glUniform1f(glGetUniformLocation(m_id, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader)
{
	if (useShader) use();
	glUniform1i(glGetUniformLocation(m_id, name), value);
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader) use();
	glUniform2f(glGetUniformLocation(m_id, name), x, y);
}

void Shader::setVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader) use();
	glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader) use();
	glUniform3f(glGetUniformLocation(m_id, name), x, y, z);
}

void Shader::setVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader) use();
	glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader) use();
	glUniform4f(glGetUniformLocation(m_id, name), x, y, z, w);
}

void Shader::setVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader) use(); 
	glUniform4f(glGetUniformLocation(m_id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader) use();
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, false, glm::value_ptr(matrix));
}

unsigned int Shader::getId()
{
	return m_id;
}