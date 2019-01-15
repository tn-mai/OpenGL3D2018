/**
* @file Actor.h
*/
#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include <GL/glew.h>
#include "Shader.h"
#include "MeshList.h"
#include <glm/vec3.hpp>
#include <vector>
#include <memory>

/**
* ������.
*/
struct Rect
{
  glm::vec3 origin;
  glm::vec3 size;
};

/**
* �V�[���ɔz�u����I�u�W�F�N�g.
*/
class Actor
{
public:
  Actor() = default;
  virtual ~Actor() = default;

  void Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
  void Finalize();

  virtual void Update(float deltTIme);

public:
  int mesh = 0;
  GLuint texture = 0;

  glm::vec3 position = glm::vec3(0);
  glm::vec3 rotation = glm::vec3(0);
  glm::vec3 scale = glm::vec3(1);

  glm::vec3 velocity = glm::vec3(0);
  glm::vec3 tmpVelocity = glm::vec3(0);
  int health = 0;
  Rect colLocal;
  Rect colWorld;
};

Actor* FindAvailableActor(std::vector<Actor*>&);
void UpdateActorList(std::vector<Actor*>&, float);
void RenderActorList(std::vector<Actor*>&, Shader::Program&, MeshList&);
void ClearActorList(std::vector<Actor*>&);

/**
*
*/
class PlayerActor : public Actor
{
public:
  virtual ~PlayerActor() = default;
  virtual void Update(float deltaTime) override;

public:
  float direction = 0;

private:
  float downAngle = 0;
};

/**
*
*/
class BulletActor : public Actor
{
public:
  virtual ~BulletActor() = default;
  virtual void Update(float deltaTime) override;
};

/**
*
*/
class ZombieActor : public Actor
{
public:
  virtual ~ZombieActor() = default;
  virtual void Update(float deltaTime) override;

public:
  Actor* target = nullptr;
  float attackingTimer = 5.0f;
  bool isAttacking = false;
  float baseSpeed = 1.0f;
};
bool DetectCollision(const Actor&, const Actor&);

// �Փ˂�����(0=��, 1=�E, 2=��, 3=��, 4=��, 5=��O).
enum class CollisionPlane
{
  none = -1, // �Փ˂Ȃ�.
  negativeX = 0, // ����.
  positiveX, // �E��.
  negativeY, // ����.
  positiveY, // �㑤.
  negativeZ, // ����.
  positiveZ, // ��O��.
};

struct CollisionTime
{
  float time; // �Փ˂�������.
  CollisionPlane plane; // �Փ˂�����.
};

CollisionTime FindCollisionTime(const Actor&, const Actor&, float);

#endif // ACTOR_H_INCLUDED