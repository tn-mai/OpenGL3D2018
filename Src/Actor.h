/**
* @file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>

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

  void Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
  void Finalize();

  void Update();

public:
  int mesh = 0;
  GLuint texture = 0;

  glm::vec3 position = glm::vec3(0);
  glm::vec3 rotation = glm::vec3(0);
  glm::vec3 scale = glm::vec3(1);

  glm::vec3 velocity = glm::vec3(0);
  int health = 0;
  Rect colLocal;
  Rect colWorld;
};

using ActorList = std::vector<Actor>;
using ActorPtrList = std::vector<Actor*>;

bool DetectCollision(const Actor&, const Actor&);

struct CollidePoint
{
  bool hasCollide;
  glm::vec3 point;
};

CollidePoint FindCollidePoint(const Actor&, const Actor&, float);

#endif // ACTOR_H_INCLUDED