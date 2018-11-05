/**
* @file MeshList.cpp
*/
#include "MeshList.h"
#include "Geometry.h"
#include <iostream>

/**
* ���f���f�[�^���i�[���閼�O���.
*/
namespace Model {

// �؂̃��f��.
namespace Tree {

const Vertex vertices[] = {
  { { 0.00f, 5.0f, 0.00f}, {0.5f, 0.8f, 0.3f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 1.5f,-1.10f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },
  { { 0.00f, 4.0f, 0.00f}, {0.2f, 0.1f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 0.0f,-0.37f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },
};

const GLushort indices[] = {
  0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
  4, 5, 6, 4, 6, 7, 4, 7, 5,
};

} // namespace Tree

// �Ƃ̃��f��.
namespace House {

const Vertex vertices[] = {
  { { 2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 1.000f, 0.00f }, { 0.71f, 0.0f, 0.71f } },
  { { 3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 1.000f, 0.69f }, { 0.71f, 0.0f, 0.71f } },
  { { 0.0f, 6.0f, 3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.875f, 1.00f }, { 0.00f, 0.0f, 1.00f } },
  { {-3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.750f, 0.69f }, {-0.71f, 0.0f, 0.71f } },
  { {-2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.750f, 0.00f }, {-0.71f, 0.0f, 0.71f } },

  { {-2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.500f, 0.00f }, {-0.71f, 0.0f,-0.71f } },
  { {-3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.500f, 0.69f }, {-0.71f, 0.0f,-0.71f } },
  { { 0.0f, 6.0f,-3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.375f, 1.00f }, { 0.00f, 0.0f,-1.00f } },
  { { 3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.250f, 0.69f }, { 0.71f, 0.0f,-0.71f } },
  { { 2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.250f, 0.00f }, { 0.71f, 0.0f,-0.71f } },

  { { 2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.000f, 0.00f }, { 0.71f, 0.0f, 0.71f } },
  { { 3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.000f, 0.69f }, { 0.71f, 0.0f, 0.71f } },

  { { 0.0f, 6.0f, 3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.750f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f,-3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.500f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f,-3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.250f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f, 3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.000f, 1.00f }, { 0.00f, 1.0f, 0.00f } }, };

const GLushort indices[] = {
  0, 1, 3, 3, 4, 0, 1, 2, 3,
  5, 6, 8, 8, 9, 5, 6, 7, 8,
  9, 8, 11, 11, 10, 9,
  4, 3, 6, 6, 5, 4,
  3, 12, 13, 13, 6, 3,
  8, 14, 15, 15, 11, 8,
};
} // namespace House

// ��̃��f��.
namespace Rock {

const Vertex vertices[] = {
  { { 0.8f, 0.8f, 0.8f}, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }, { 0.58f, 0.58f, 0.58f } },
  { { 0.8f, 1.0f,-0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.5f, 0.5f }, { 0.58f, 0.58f,-0.58f } },
  { {-0.8f, 1.2f,-0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.5f }, {-0.58f, 0.58f,-0.58f } },
  { {-0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f }, {-0.58f, 0.58f, 0.58f } },

  { { 0.6f, 0.0f, 1.4f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f }, { 0.71f, 0.0f, 0.71f } },
  { { 1.4f, 0.0f,-0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f }, { 0.71f, 0.0f,-0.71f } },
  { {-0.6f, 0.0f,-1.4f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 1.0f }, {-0.71f, 0.0f,-0.71f } },
  { {-1.4f, 0.0f, 0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f }, {-0.71f, 0.0f, 0.71f } },
};

const GLushort indices[] = {
  0, 1, 2, 2, 3, 0,
  4, 5, 1, 1, 0, 4,
  5, 6, 2, 2, 1, 5,
  6, 7, 3, 3, 2, 6,
  7, 4, 0, 0, 3, 7,
};

} // namespace Rock

// �n�ʂ̃��f��.
namespace Ground {

const Vertex vertices[] = {
  { {-20.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  0.0f,  0.0f }, { 0.0f, 1.0f, 0.0f } },
  { {-10.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  5.0f,  0.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f,  0.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 10.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 15.0f,  0.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 20.0f,  0.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f, 10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  0.0f,  5.0f }, { 0.0f, 1.0f, 0.0f } },
  { {-10.0f, 0.0f, 10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  5.0f,  5.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f, 10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f,  5.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 10.0f, 0.0f, 10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 15.0f,  5.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f, 10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 20.0f,  5.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f,  0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  0.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { {-10.0f, 0.0f,  0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  5.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f,  0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 10.0f, 0.0f,  0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 15.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f,  0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 20.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f,-10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  0.0f, 15.0f }, { 0.0f, 1.0f, 0.0f } },
  { {-10.0f, 0.0f,-10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  5.0f, 15.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f,-10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 15.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 10.0f, 0.0f,-10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 15.0f, 15.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f,-10.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 20.0f, 15.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  0.0f, 20.0f }, { 0.0f, 1.0f, 0.0f } },
  { {-10.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, {  5.0f, 20.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 20.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 10.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 15.0f, 20.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 20.0f, 20.0f }, { 0.0f, 1.0f, 0.0f } },
};

const GLushort indices[] = {
  0, 1, 6, 6, 5, 0, 1, 2, 7, 7, 6, 1, 2, 3, 8, 8, 7, 2, 3, 4, 9, 9, 8, 3,
  5, 6, 11, 11, 10, 5, 6, 7, 12, 12, 11, 6, 7, 8, 13, 13, 12, 7, 8, 9, 14, 14, 13, 8,
  10, 11, 16, 16, 15, 10, 11, 12, 17, 17, 16, 11, 12, 13, 18, 18, 17, 12, 13, 14, 19, 19, 18, 13,
  15, 16, 21, 21, 20, 15, 16, 17, 22, 22, 21, 16, 17, 18, 23, 23, 22, 17, 18, 19, 24, 24, 23, 18,
};

} // namespace Ground

} // namespace Model

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
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, sizeof(Vertex::normal) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return vao;
}

/**
* �R���X�g���N�^.
*/
MeshList::MeshList()
{
}

/**
* �f�X�g���N�^.
*/
MeshList::~MeshList()
{
  Free();
}

/**
* ���f���f�[�^����Mesh�̃��X�g���쐬����.
*
* @retval true  �쐬����.
* @retval false �쐬���s.
*/
bool MeshList::Allocate()
{
  Free();

  meshes.reserve(1'000);

  vbo = CreateVBO(100'000 * sizeof(Vertex), nullptr);
  ibo = CreateIBO(100'000 * sizeof(GLushort), nullptr);
  vao = CreateVAO(vbo, ibo);
  if (!vbo || !ibo || !vao) {
    std::cerr << "ERROR: VAO�̍쐬�Ɏ��s.\n";
    return false;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

  meshes.push_back({ GL_TRIANGLES, sizeof(Model::Tree::indices) / sizeof(GLushort), (const GLvoid*)iboEnd, (GLint)(vboEnd / sizeof(Vertex)) });
  glBufferSubData(GL_ARRAY_BUFFER, vboEnd, sizeof(Model::Tree::vertices), Model::Tree::vertices);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iboEnd, sizeof(Model::Tree::indices), Model::Tree::indices);
  vboEnd += sizeof(Model::Tree::vertices);
  iboEnd += sizeof(Model::Tree::indices);

  meshes.push_back({ GL_TRIANGLES, sizeof(Model::House::indices) / sizeof(GLushort), (const GLvoid*)iboEnd, (GLint)(vboEnd / sizeof(Vertex)) });
  glBufferSubData(GL_ARRAY_BUFFER, vboEnd, sizeof(Model::House::vertices), Model::House::vertices);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iboEnd, sizeof(Model::House::indices), Model::House::indices);
  vboEnd += sizeof(Model::House::vertices);
  iboEnd += sizeof(Model::House::indices);

  meshes.push_back({ GL_TRIANGLES, sizeof(Model::Rock::indices) / sizeof(GLushort), (const GLvoid*)iboEnd, (GLint)(vboEnd / sizeof(Vertex)) });
  glBufferSubData(GL_ARRAY_BUFFER, vboEnd, sizeof(Model::Rock::vertices), Model::Rock::vertices);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iboEnd, sizeof(Model::Rock::indices), Model::Rock::indices);
  vboEnd += sizeof(Model::Rock::vertices);
  iboEnd += sizeof(Model::Rock::indices);

  meshes.push_back({ GL_TRIANGLES, sizeof(Model::Ground::indices) / sizeof(GLushort), (const GLvoid*)iboEnd, (GLint)(vboEnd / sizeof(Vertex)) });
  glBufferSubData(GL_ARRAY_BUFFER, vboEnd, sizeof(Model::Ground::vertices), Model::Ground::vertices);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iboEnd, sizeof(Model::Ground::indices), Model::Ground::indices);
  vboEnd += sizeof(Model::Ground::vertices);
  iboEnd += sizeof(Model::Ground::indices);

  return true;
}

/**
* ���b�V�����X�g��j������.
*/
void MeshList::Free()
{
  if (vao) {
    glDeleteVertexArrays(1, &vao);
    vao = 0;
  }
  if (ibo) {
    glDeleteBuffers(1, &ibo);
    ibo = 0;
  }
  if (vbo) {
    glDeleteBuffers(1, &vbo);
    vbo = 0;
  }

  vboEnd = 0;
  iboEnd = 0;
  meshes.clear();
}

/**
* �`��Ɏg�p����VAO��ݒ肷��.
*/
void MeshList::BindVertexArray()
{
  glBindVertexArray(vao);
}

/**
* ���b�V�����擾����.
*
* @param index �擾���郁�b�V���̔ԍ�.
*
* @return index�Ԗڂ̃��b�V��.
*/
const Mesh& MeshList::operator[](size_t index) const
{
  return meshes[index];
}
