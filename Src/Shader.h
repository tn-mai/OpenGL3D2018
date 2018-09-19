/**
* @file Shader.h
*/
#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <GL/glew.h>

namespace Shader {

GLuint CreateShaderProgram(const GLchar* vsCode, const GLchar* fsCode);

} // namespace Shader

#endif
