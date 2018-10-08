/**
* @file Texture.cpp
*/
#include "Texture.h"
#include <iostream>

/// テクスチャ関連の関数やクラスを格納する名前空間.
namespace Texture {

/**
* 2Dテクスチャを作成する.
*
* @param width   テクスチャの幅(ピクセル数).
* @param height  テクスチャの高さ(ピクセル数).
* @param data    テクスチャデータへのポインタ.
*
* @retval 0以外  作成したテクスチャ・オブジェクトのID.
* @retval 0      テクスチャの作成に失敗.
*/
GLuint CreateImage2D(GLsizei width, GLsizei height, const void* data)
{
  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  const GLenum result = glGetError();
  if (result != GL_NO_ERROR) {
    std::cerr << "ERROR: テクスチャの作成に失敗(0x" << std::hex << result << ").";
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &id);
    return 0;
  }

  // テクスチャのパラメータを設定する.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  return id;
}

} // namespace Texture