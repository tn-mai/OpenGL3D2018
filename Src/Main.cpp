/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

/// 2D�x�N�g���^.
struct Vector2
{
  float x, y;
};

/// 3D�x�N�g���^.
struct Vector3
{
  float x, y, z;
};

/// RGBA�J���[�^.
struct Color
{
  float r, g, b, a;
};

/// ���_�f�[�^�^.
struct Vertex
{
  Vector3 position; ///< ���W
  Color color; ///< �F
  Vector2 texCoord; ///< �e�N�X�`�����W.
};

/// ���_�f�[�^.
const Vertex vertices[] = {
  // ��
  { { 0.00f, 5.0f, 0.00f}, {0.5f, 0.8f, 0.3f, 1.0f} },
  { { 0.00f, 1.5f,-1.10f}, {0.1f, 0.3f, 0.0f, 1.0f} },
  { {-0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f} },
  { { 0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f} },
  { { 0.00f, 4.0f, 0.00f}, {0.2f, 0.1f, 0.0f, 1.0f} },
  { { 0.00f, 0.0f,-0.37f}, {0.5f, 0.3f, 0.2f, 1.0f} },
  { {-0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f} },
  { { 0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f} },

  // ��
  { { 2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, {-2.0f,-2.0f } },
  { { 3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, {-2.0f, 0.8f } },
  { { 0.0f, 6.0f, 3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.0f, 2.0f } },
  { {-3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 2.0f, 0.8f } },
  { {-2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 2.0f,-2.0f } },

  { {-2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, {-2.0f,-2.0f } },
  { {-3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, {-2.0f, 0.8f } },
  { { 0.0f, 6.0f,-3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.0f, 2.0f } },
  { { 3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 2.0f, 0.8f } },
  { { 2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 2.0f,-2.0f } },

  { { 3.0f, 4.0f, 3.0f}, {0.2f, 0.1f, 0.1f, 1.0f}, {-2.0f,-2.0f } },
  { { 0.0f, 6.0f, 3.0f}, {0.3f, 0.2f, 0.2f, 1.0f}, { 0.0f,-2.0f } },
  { {-3.0f, 4.0f, 3.0f}, {0.2f, 0.1f, 0.1f, 1.0f}, { 2.0f,-2.0f } },
  { {-3.0f, 4.0f,-3.0f}, {0.2f, 0.1f, 0.1f, 1.0f}, { 2.0f, 2.0f } },
  { { 0.0f, 6.0f,-3.0f}, {0.3f, 0.2f, 0.2f, 1.0f}, { 0.0f, 2.0f } },
  { { 3.0f, 4.0f,-3.0f}, {0.2f, 0.1f, 0.1f, 1.0f}, {-2.0f, 2.0f } },

  // ��
  { { 0.4f, 0.4f, 0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.5f, 0.0f } },
  { { 0.4f, 0.5f,-0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.5f, 0.5f } },
  { {-0.4f, 0.6f,-0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.0f, 0.5f } },
  { {-0.4f, 0.4f, 0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.0f, 0.0f } },

  { { 0.3f, 0.0f, 0.7f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 1.0f, 0.0f } },
  { { 0.7f, 0.0f,-0.3f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 1.0f, 1.0f } },
  { {-0.3f, 0.0f,-0.7f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 0.0f, 1.0f } },
  { {-0.7f, 0.0f, 0.3f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 0.0f, 0.0f } },

  // ���g�p
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

/// �C���f�b�N�X�f�[�^.
const GLushort indices[] = {
  // ��
  0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
  4, 5, 6, 4, 6, 7, 4, 7, 5,

  // ��
  0, 1, 3, 3, 4, 0, 1, 2, 3,
  5, 6, 8, 8, 9, 5, 6, 7, 8,
  9, 8, 1, 1, 0, 9,
  4, 3, 6, 6, 5, 4,
  15, 14, 11, 11, 10, 15,
  12, 11, 14, 14, 13, 12,

  // ��
  0, 1, 2, 2, 3, 0,
  4, 5, 1, 1, 0, 4,
  5, 6, 2, 2, 1, 5,
  6, 7, 3, 3, 2, 6,
  7, 4, 0, 0, 3, 7,

  12, 13, 16, 13, 14, 16, 14, 15, 16, 15, 12, 16,
  13, 12, 17, 14, 13, 17, 15, 14, 17, 12, 15, 17,

  0, 1, 2, 2, 3, 0,
  4, 5, 6, 7, 8, 9,
};

/**
* �|���S���\���P��.
*/
struct Mesh
{
  GLenum mode; ///< �v���~�e�B�u�̎��.
  GLsizei count; ///< �`�悷��C���f�b�N�X��.
  const GLvoid* indices; ///< �`��J�n�C���f�b�N�X�̃o�C�g�I�t�Z�b�g.
  GLint baseVertex; ///< �C���f�b�N�X0�Ƃ݂Ȃ���钸�_�z����̈ʒu.
};

/**
* ���b�V���z��.
*/
const Mesh meshList[] = {
  { GL_TRIANGLES, 3 * 7, (const GLvoid*)0, 0 },
  { GL_TRIANGLES, 3 * 14, (const GLvoid*)(21 * sizeof(indices[0])), 8 },
  { GL_TRIANGLES, 3 * 10, (const GLvoid*)(63 * sizeof(indices[0])), 24 },
};


/// ���_�V�F�[�_.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexCoord; \n"
"layout(location=0) out vec4 outColor; \n"
"layout(location=1) out vec2 outTexCoord; \n"
"uniform mat4x4 matMVP; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  outTexCoord = vTexCoord; \n"
"  gl_Position = matMVP * vec4(vPosition, 1.0); \n"
"} \n";

/// �t���O�����g�V�F�[�_.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexCoord; \n"
"out vec4 fragColor; \n"
"uniform sampler2D texColor; \n"
"void main() { \n"
"  fragColor = inColor * texture(texColor, inTexCoord); \n"
"} \n";

/**
* Vertex Buffer Object���쐬����.
*
* @param size ���_�f�[�^�̃T�C�Y.
* @param data ���_�f�[�^�ւ̃|�C���^.
*
* @return �쐬����VBO.
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
* Index Buffer Object���쐬����.
*
* @param size �C���f�b�N�X�f�[�^�̃T�C�Y.
* @param data �C���f�b�N�X�f�[�^�ւ̃|�C���^.
*
* @return �쐬����IBO.
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
  GLuint ibo = 0;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return ibo;
}

/**
* Vertex Array Object���쐬����.
*
* @param vbo VAO�Ɋ֘A�t������VBO.
* @param ibo VAO�Ɋ֘A�t������IBO.
*
* @return �쐬����VAO.
*/
GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  const GLsizei stride = sizeof(Vertex);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, position)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, color)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, texCoord)));
  glBindVertexArray(0);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);
  return vao;
}

/// �G���g���[�|�C���g.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL Tutorial")) {
    return 1;
  }

  const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
  const GLuint ibo = CreateIBO(sizeof(indices), indices);
  const GLuint vao = CreateVAO(vbo, ibo);
  const GLuint shaderProgram = Shader::Build(vsCode, fsCode);
  if (!vbo || !ibo || !vao || !shaderProgram) {
    return 1;
  }

  // uniform�ϐ��̈ʒu���擾.
  glUseProgram(shaderProgram);
  const GLint matMVPLoc = glGetUniformLocation(shaderProgram, "matMVP");
  if (matMVPLoc < 0) {
    std::cerr << "ERROR: uniform�ϐ�'matMVP'�̈ʒu���擾�ł��܂���.\n";
    return 1;
  }
  const GLint texColorLoc = glGetUniformLocation(shaderProgram, "texColor");
  if (texColorLoc >= 0) {
    glUniform1i(texColorLoc, 0);
  }
  glUseProgram(0);

  // �e�N�X�`�����쐬����.
  const int tw = 8; // �摜�̕�.
  const int th = 8; // �摜�̍���.
  const GLuint B = 0xff'00'00'00; // ��.
  const GLuint W = 0xff'ff'ff'ff; // ��.
  const GLuint imageData[tw * th] = {
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    B, B, B, B, B, B, B, B,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    B, B, B, B, B, B, B, B,
  };
  GLuint texId = Texture::CreateImage2D(tw, th, imageData);

  // ���C�����[�v.
  while (!window.ShouldClose()) {
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���_����]�ړ�������.
    static float degree = 0.0f;
    degree += 0.1f;
    if (degree >= 360.0f) { degree -= 360.0f; }
    const glm::vec3 viewPos = glm::rotate(glm::mat4(1), glm::radians(degree), glm::vec3(0, 1, 0)) * glm::vec4(-20, 30, -30, 1);

    glUseProgram(shaderProgram);

    // ���W�ϊ��s����쐬����.
    const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
    const glm::mat4x4 matView = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);

    const float treeCount = 10;
    for (float i = 0; i < treeCount; ++i) {
      const float x = std::cos(3.14f * 2 / treeCount * i) * 8;
      const float z = std::sin(3.14f * 2 / treeCount * i) * 8;
      const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));
      const glm::mat4x4 matMVP = matProj * matView * matModel;
      glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
      glDrawElementsBaseVertex(meshList[0].mode, meshList[0].count, GL_UNSIGNED_SHORT, meshList[0].indices, meshList[0].baseVertex);
    }

    {
      const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
      const glm::mat4x4 matMVP = matProj * matView * matModel;
      glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
      glDrawElementsBaseVertex(meshList[1].mode, meshList[1].count, GL_UNSIGNED_SHORT, meshList[1].indices, meshList[1].baseVertex);
    }

    {
      const glm::mat4x4 matModel = glm::scale(glm::translate(glm::mat4(1), glm::vec3(4, 0, 0)), glm::vec3(1));
      const glm::mat4x4 matMVP = matProj * matView * matModel;
      glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
      glDrawElementsBaseVertex(meshList[2].mode, meshList[2].count, GL_UNSIGNED_SHORT, meshList[2].indices, meshList[2].baseVertex);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    window.SwapBuffers();
  }

  glDeleteTextures(1, &texId);
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &vao);

  return 0;
}
