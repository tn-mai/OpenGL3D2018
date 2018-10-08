/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <GL/glew.h>

namespace Texture {

GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data);

} // namespace Texture


#endif // TEXTURE_H_INCLUDED