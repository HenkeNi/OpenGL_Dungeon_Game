#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader() {}

	Shader& use(); // set current shader as active
	void compile(const char* vertSrc, const char* fragSrc, const char* geoSrc = nullptr);

	// utility functions
	void setFloat    (const char* name, float value, bool useShader = false);
	void setInteger  (const char* name, int value, bool useShader = false);
	void setVector2f (const char* name, float x, float y, bool useShader = false);
	void setVector2f (const char* name, const glm::vec2& value, bool useShader = false);
	void setVector3f (const char* name, float x, float y, float z, bool useShader = false);
	void setVector3f (const char* name, const glm::vec3& value, bool useShader = false);
	void setVector4f (const char* name, float x, float y, float z, float w, bool useShader = false);
	void setVector4f (const char* name, const glm::vec4& value, bool useShader = false);
	void setMatrix4  (const char* name, const glm::mat4& matrix, bool useShader = false);

	unsigned int getId();

private:
	unsigned int compileShader(const char* src, unsigned int type);
	void checkCompileErrors(unsigned int object, std::string type); // check if compiling or linking failed

private:
	unsigned int m_id; 

};

