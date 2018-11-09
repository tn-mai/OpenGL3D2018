/**
* @file MeshList.cpp
*/
#include "MeshList.h"
#include "Geometry.h"
#include <iostream>

// 木のモデル.
const Vertex vTree[] = {
  { { 0.00f, 5.0f, 0.00f}, {0.5f, 0.8f, 0.3f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 1.5f,-1.10f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },
  { { 0.00f, 4.0f, 0.00f}, {0.2f, 0.1f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 0.0f,-0.37f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },
};

const GLushort iTree[] = {
  0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
  4, 5, 6, 4, 6, 7, 4, 7, 5,
};

// 家のモデル.
const Vertex vHouse[] = {
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

const GLushort iHouse[] = {
  0, 1, 3, 3, 4, 0, 1, 2, 3,
  5, 6, 8, 8, 9, 5, 6, 7, 8,
  9, 8, 11, 11, 10, 9,
  4, 3, 6, 6, 5, 4,
  3, 12, 13, 13, 6, 3,
  8, 14, 15, 15, 11, 8,
};
// 岩のモデル.

const Vertex vRock[] = {
  { { 0.8f, 0.8f, 0.8f}, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.5f, 0.0f }, { 0.58f, 0.58f, 0.58f } },
  { { 0.8f, 1.0f,-0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.5f, 0.5f }, { 0.58f, 0.58f,-0.58f } },
  { {-0.8f, 1.2f,-0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.5f }, {-0.58f, 0.58f,-0.58f } },
  { {-0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f }, {-0.58f, 0.58f, 0.58f } },

  { { 0.6f, 0.0f, 1.4f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f }, { 0.71f, 0.0f, 0.71f } },
  { { 1.4f, 0.0f,-0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f }, { 0.71f, 0.0f,-0.71f } },
  { {-0.6f, 0.0f,-1.4f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 1.0f }, {-0.71f, 0.0f,-0.71f } },
  { {-1.4f, 0.0f, 0.6f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f }, {-0.71f, 0.0f, 0.71f } },
};

const GLushort iRock[] = {
  0, 1, 2, 2, 3, 0,
  4, 5, 1, 1, 0, 4,
  5, 6, 2, 2, 1, 5,
  6, 7, 3, 3, 2, 6,
  7, 4, 0, 0, 3, 7,
};

// 地面のモデル.
const Vertex vGround[] = {
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

const GLushort iGround[] = {
  0, 1, 6, 6, 5, 0, 1, 2, 7, 7, 6, 1, 2, 3, 8, 8, 7, 2, 3, 4, 9, 9, 8, 3,
  5, 6, 11, 11, 10, 5, 6, 7, 12, 12, 11, 6, 7, 8, 13, 13, 12, 7, 8, 9, 14, 14, 13, 8,
  10, 11, 16, 16, 15, 10, 11, 12, 17, 17, 16, 11, 12, 13, 18, 18, 17, 12, 13, 14, 19, 19, 18, 13,
  15, 16, 21, 21, 20, 15, 16, 17, 22, 22, 21, 16, 17, 18, 23, 23, 22, 17, 18, 19, 24, 24, 23, 18,
};

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
* Index Buffer Objectを作成する.
*
* @param size インデックスデータのサイズ.
* @param data インデックスデータへのポインタ.
*
* @return 作成したIBO.
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
* Vertex Array Objectを作成する.
*
* @param vbo VAOに関連付けられるVBO.
* @param ibo VAOに関連付けられるIBO.
*
* @return 作成したVAO.
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
  glDeleteBuffers(1, &ibo);
  glDeleteBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return vao;
}

/**
* コンストラクタ.
*/
MeshList::MeshList()
{
}

/**
* デストラクタ.
*/
MeshList::~MeshList()
{
  Free();
}

/**
* モデルデータからMeshのリストを作成する.
*
* @retval true  作成成功.
* @retval false 作成失敗.
*/
bool MeshList::Allocate()
{
  Free();

  meshes.reserve(100);
  tmpVertices.reserve(10'000);
  tmpIndices.reserve(10'000);

  Add(std::begin(vTree), std::end(vTree), std::begin(iTree), std::end(iTree));
  Add(std::begin(vHouse), std::end(vHouse), std::begin(iHouse), std::end(iHouse));
  Add(std::begin(vRock), std::end(vRock), std::begin(iRock), std::end(iRock));
  Add(std::begin(vGround), std::end(vGround), std::begin(iGround), std::end(iGround));

  GLuint ibo = CreateIBO(tmpIndices.size() * sizeof(GLushort), tmpIndices.data());
  GLuint vbo = CreateVBO(tmpVertices.size() * sizeof(Vertex), tmpVertices.data());
  vao = CreateVAO(vbo, ibo);

  std::vector<Vertex>().swap(tmpVertices);
  std::vector<GLushort>().swap(tmpIndices);

  if (!vbo || !ibo || !vao) {
    std::cerr << "ERROR: VAOの作成に失敗.\n";
    return false;
  }

  return true;
}

/**
* メッシュリストを破棄する.
*/
void MeshList::Free()
{
  glDeleteVertexArrays(1, &vao);
  vao = 0;
  std::vector<Mesh>().swap(meshes);
}

/**
* メッシュを追加する.
*
* @param vBegin  頂点データのポインタ.
* @param vEnd    頂点データの終端のポインタ.
* @param iBegin  インデックスデータのポインタ.
* @param iEnd    インデックスデータの終端のポインタ.
*/
void MeshList::Add(const Vertex* vBegin, const Vertex* vEnd, const GLushort* iBegin, const GLushort* iEnd)
{
  Mesh m;
  m.mode = GL_TRIANGLES;
  m.count = iEnd - iBegin;
  m.indices = (const GLvoid*)(tmpIndices.size() * sizeof(GLushort));
  m.baseVertex = (GLint)tmpVertices.size();
  meshes.push_back(m);

  tmpVertices.insert(tmpVertices.end(), vBegin, vEnd);
  tmpIndices.insert(tmpIndices.end(), iBegin, iEnd);
}

/**
* 描画に使用するVAOを設定する.
*/
void MeshList::BindVertexArray()
{
  glBindVertexArray(vao);
}

/**
* メッシュを取得する.
*
* @param index 取得するメッシュの番号.
*
* @return index番目のメッシュ.
*/
const Mesh& MeshList::operator[](size_t index) const
{
  return meshes[index];
}
