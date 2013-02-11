#ifndef shader_h
#define shader_h
#include <string>
#include <GL\glew.h>

#include <GL\GL.h>
#include <GL\GLU.h>
#include "shader_util.h"
#include <vector>
#include <string>
#include <sstream>
#include "ShaderUniforms.h"
#include "ShaderAttributes.h"

class Shader
{
public:
	Shader(std::string name,unsigned int numUniforms = ShaderUniforms::NUM_UNIFORMS,unsigned int numAttributes = ShaderAttributes::NUM_ATTRIBUTES,unsigned int numUniformStructs = ShaderUniforms::NUM_UNIFORMS);
	Shader(std::string vs,std::string fs,unsigned int numUniforms = ShaderUniforms::NUM_UNIFORMS,unsigned int numAttributes = ShaderAttributes::NUM_ATTRIBUTES,unsigned int numUniformStructs = ShaderUniforms::NUM_UNIFORMS);
	~Shader(void);
	
	void setUniformMat4f(unsigned int uniform,float*value);
	void setUniformFloat(unsigned int uniform,float value);
	void setUniformVec3f(unsigned int uniform,float*value);
	void setUniformVec3f(unsigned int uniform,float v1,float v2,float v3);
	void setUniformVec4f(unsigned int uniform,float v1,float v2,float v3,float v4);
	void setUniformStructVec3f(unsigned int structArray,int index, unsigned int uniform,float v1,float v2,float v3);
	void setUniformStructVec4f(unsigned int structArray,int index, unsigned int uniform,float v1,float v2,float v3,float v4);
	void setUniformStructFloat(unsigned int structArray,int index, unsigned int uniform,float value);
	void setUniformInt(unsigned int uniform,int value);

	void bindUniform(unsigned int uniform,std::string name);
	void bindUniformStructArray(unsigned int uniform,unsigned int arraySize,unsigned int memberCount,const char*structName,const char **structMemberNames);
	GLint **getStructArray(unsigned int uniform);
	GLint*getStruct(unsigned int uniform,int i);
	void bindAttribute(unsigned int attribute,std::string name);
	void bind();
	void unbind();
	GLint* getAttributes();
private:
	void init();
	bool bound;
	GLint program;
	GLint*uniforms;
	GLint*attributes;

	unsigned int numUniforms,numAttributes,numUniformStructs;
	GLint *** uniformStructs;

};







#endif