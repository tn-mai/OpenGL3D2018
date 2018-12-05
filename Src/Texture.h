/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <GL/glew.h>

namespace Texture {

GLuint CreateImage2D(GLsizei width, GLsizei height, const GLvoid* data, GLenum format, GLenum type);
GLuint LoadImage2D(const char* path);

/**
* テクスチャ・イメージ.
*/
class Image2D
{
public:
  explicit Image2D(GLuint texId);
  ~Image2D();
  GLuint Get() const;

private:
  GLuint id = 0;
};

} // namespace Texture

#endif // TEXTURE_H_INCLUDED