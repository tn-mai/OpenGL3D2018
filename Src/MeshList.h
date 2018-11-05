/**
* @file MeshList.h
*/
#ifndef MESHLIST_H_INCLUDED
#define MESHLIST_H_INCLUDED
#include <GL/glew.h>
#include <vector>

struct Mesh;

/**
* メッシュ管理クラス.
*/
class MeshList
{
public:
  MeshList();
  ~MeshList();
  MeshList(const MeshList&) = default;
  MeshList& operator=(const MeshList&) = default;

  bool Allocate();
  void Free();

  void BindVertexArray();
  const Mesh& operator[](size_t index) const;

private:
  GLuint vbo = 0;
  GLuint ibo = 0;
  GLuint vao = 0;

  GLintptr vboEnd = 0;
  GLintptr iboEnd = 0;

  std::vector<Mesh> meshes;
};

#endif // MESHLIST_H_INCLUDED