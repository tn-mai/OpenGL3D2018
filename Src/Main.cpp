/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include <iostream>
#include <vector>

/// 3Dベクトル型.
struct Vector3
{
  float x, y, z;
};

/// RGBAカラー型.
struct Color
{
  float r, g, b, a;
};

/// 頂点データ型.
struct Vertex
{
  Vector3 position; ///< 座標
  Color color; ///< 色
};

/// 頂点データ.
const Vertex vertices[] = {
  { {-0.25f,  0.0f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.25f,  0.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { { 0.0f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },

  { {-0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.0f,  0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { {-0.25f,  0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },

  { { 0.0f,  0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.5f,  0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { { 0.25f,  0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },
};

/// 頂点シェーダ.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=0) out vec4 outColor; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  gl_Position = vec4(vPosition, 1.0); \n"
"} \n";

/// フラグメントシェーダ.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"out vec4 fragColor; \n"
"void main() { \n"
"  fragColor = inColor; \n"
"} \n";

/**
* Vertex Buffer Objectを作成する.
*
* @param size 頂点データのサイズ.
* @param data 頂点データへのポインタ.
*
* @return 作成したVBO.
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return vbo;
}

/**
* Vertex Array Objectを作成する.
*
* @param vbo VAOに関連付けられるVBO.
*
* @return 作成したVAO.
*/
GLuint CreateVAO(GLuint vbo)
{
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  const GLsizei stride = sizeof(Vertex);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, position)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, color)));
  glBindVertexArray(0);
  glDeleteBuffers(1, &vbo);
  return vao;
}

/// エントリーポイント.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL Tutorial")) {
    return 1;
  }

  const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
  const GLuint vao = CreateVAO(vbo);
  const GLuint shaderProgram = Shader::Build(vsCode, fsCode);
  if (!vbo || !vao || !shaderProgram) {
    return 1;
  }

  // メインループ.
  while (!window.ShouldClose()) {
    glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));

    window.SwapBuffers();
  }

  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &vao);

  return 0;
}
