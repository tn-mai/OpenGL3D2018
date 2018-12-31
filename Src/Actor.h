/**
* @file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <GL/glew.h>
#include <glm/vec3.hpp>

/**
* 直方体.
*/
struct Rect
{
  glm::vec3 origin;
  glm::vec3 size;
};

/**
* シーンに配置するオブジェクト.
*/
class Actor
{
public:
  Actor() = default;
  ~Actor() = default;

  void Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
  {
    this->mesh = mesh;
    texture = tex;
    position = pos;
    rotation = rot;
    this->scale = scale;

    health = hp;
  }
  void Finalize() {}

public:
  int mesh = 0;
  GLuint texture = 0;

  glm::vec3 position = glm::vec3(0);
  glm::vec3 rotation = glm::vec3(0);
  glm::vec3 scale = glm::vec3(1);

  glm::vec3 velocity = glm::vec3(0);
  int health = 0;
  Rect collision;
};

#endif // ACTOR_H_INCLUDED