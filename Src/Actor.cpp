/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

/**
* ������.
*/
void Actor::Initialize(int mesh, GLuint tex, int hp, const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
{
  this->mesh = mesh;
  texture = tex;
  position = pos;
  rotation = rot;
  this->scale = scale;

  health = hp;
}

/**
* �I��.
*/
void Actor::Finalize()
{
}

/**
* �X�V.
*
* @param deltaTime �o�ߎ���.
*/
void Actor::Update(float deltaTime)
{
  position += velocity * deltaTime;
  colWorld.origin = colLocal.origin + position;
  colWorld.size = colLocal.size;
}

/**
* ���p�\��Actor���擾����.
*
* @param actorList �����Ώۂ̃A�N�^�[�̃��X�g.
*
* @return ���p�\��Actor�̃|�C���^.
*         ���p�\��Actor��������Ȃ����nullptr.
*/
Actor* FindAvailableActor(std::vector<Actor*>& actorList)
{
  for (auto& actor : actorList) {
    if (actor && actor->health <= 0) {
      return actor;
    }
  }
  return nullptr;
}

/**
* �A�N�^�[�̏�Ԃ��X�V����.
*
* @param actorList �X�V����A�N�^�[�̃��X�g.
* @param deltaTime �O��̍X�V����̌o�ߎ���.
*/
void UpdateActorList(std::vector<Actor*>& actorList, float deltaTime)
{
  for (auto& actor : actorList) {
    if (actor && actor->health > 0) {
      actor->Update(deltaTime);
    }
  }
}

/**
* Actor��`�悷��.
*
* @param actorList �`�悷��A�N�^�[�̃��X�g.
* @param shader    �`��Ɏg�p����V�F�[�_�[�E�I�u�W�F�N�g.
* @param meshList  �`��Ɏg�p���郁�b�V�����X�g.
*/
void RenderActorList(std::vector<Actor*>& actorList, Shader::Program& shader, MeshList& meshList)
{
  for (auto& actor : actorList) {
    if (actor && actor->health > 0) {
      shader.BindTexture(0, actor->texture);
      shader.Draw(meshList[actor->mesh], actor->position, actor->rotation, actor->scale);
    }
  }
}

/**
* �A�N�^�[���X�g����ɂ���.
*
* @param actorList ��ɂ���A�N�^�[�̃��X�g.
*/
void ClearActorList(std::vector<Actor*>& actorList)
{
  for (auto& actor : actorList) {
    delete actor;
  }
  actorList.clear();
}
/**
*
*/
void PlayerActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (health <= 0) {
    downAngle += glm::radians(-45.0f) * deltaTime;
    if (downAngle < glm::radians(-90.0f)) {
      downAngle = glm::radians(-90.0f);
    }
  }
  const glm::quat qx(glm::vec3(downAngle, 0, 0));
  const glm::quat qy(glm::vec3(0, direction, 0));
  rotation = glm::eulerAngles(qx * qy);
}

/**
*
*/
void BulletActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (glm::any(glm::lessThan(position, glm::vec3(-20)))) {
    health = 0;
  } else if (glm::any(glm::greaterThanEqual(position, glm::vec3(20)))) {
    health = 0;
  }
}

/**
*
*/
void ZombieActor::Update(float deltaTime)
{
  Actor::Update(deltaTime);
  if (!target) {
    return;
  }

  const float moveSpeed = baseSpeed * 2.0f;
  const float rotationSpeed = baseSpeed * glm::radians(60.0f);
  const float frontRange = glm::radians(15.0f);

  const glm::vec3 v = target->position - position;
  const glm::vec3 vTarget = glm::normalize(v);
  float radian = std::atan2(-vTarget.z, vTarget.x) - glm::radians(90.0f);
  if (radian <= 0) {
    radian += glm::radians(360.0f);
  }
  const glm::vec3 vZombieFront = glm::rotate(glm::mat4(1), rotation.y, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
  if (std::abs(radian - rotation.y) > frontRange) {
    const glm::vec3 vRotDir = glm::cross(vZombieFront, vTarget);
    if (vRotDir.y >= 0) {
      rotation.y += rotationSpeed * deltaTime;
      if (rotation.y >= glm::radians(360.0f)) {
        rotation.y -= glm::radians(360.0f);
      }
    } else {
      rotation.y -= rotationSpeed * deltaTime;
      if (rotation.y < 0) {
        rotation.y += glm::radians(360.0f);
      }
    }
  }

  // �\���ɐڋ߂��Ă��Ȃ���Έړ�����. �ڋ߂��Ă���΍U������.
  if (glm::length(v) > 1.0f) {
    velocity = vZombieFront * moveSpeed;
  } else {
    velocity = glm::vec3(0);
    // ����I�ɍU����ԂɂȂ�.
    if (isAttacking) {
      isAttacking = false;
      attackingTimer = 5.0f;
    } else {
      attackingTimer -= deltaTime;
      if (attackingTimer <= 0) {
        isAttacking = true;
      }
    }
  }
}

/**
* 2�̒����`�̏Փˏ�Ԃ𒲂ׂ�.
*
* @param lhs �����`����1.
* @param rhs �����`����2.
*
* @retval true  �Փ˂��Ă���.
* @retval false �Փ˂��Ă��Ȃ�.
*/
bool DetectCollision(const Actor& lhs, const Actor& rhs)
{
  return
    lhs.colWorld.origin.x < rhs.colWorld.origin.x + rhs.colWorld.size.x &&
    lhs.colWorld.origin.x + lhs.colWorld.size.x > rhs.colWorld.origin.x &&
    lhs.colWorld.origin.y < rhs.colWorld.origin.y + rhs.colWorld.size.y &&
    lhs.colWorld.origin.y + lhs.colWorld.size.y > rhs.colWorld.origin.y &&
    lhs.colWorld.origin.z < rhs.colWorld.origin.z + rhs.colWorld.size.z &&
    lhs.colWorld.origin.z + lhs.colWorld.size.z > rhs.colWorld.origin.z;
}

/**
* �Փ˂���܂ł̌o�ߎ��Ԃ��v�Z����.
*/
CollisionTime FindCollisionTime(const Actor& a, const Actor& b, float deltaTime)
{
  const glm::vec3 aMin = a.colWorld.origin;
  const glm::vec3 aMax = aMin + a.colWorld.size;
  const glm::vec3 bMin = b.colWorld.origin;
  const glm::vec3 bMax = bMin + b.colWorld.size;

  // �A�N�^�[a���Î~�A�A�N�^�[b���ړ����Ă���Ƃ݂Ȃ��A�Փ˂��N�������ŒZ�����𒲂ׂ�.
  const glm::vec3 v = (b.velocity - a.velocity) * deltaTime;
  float tfirst = -1.0f;
  float tlast = 0.0f;
  CollisionPlane plane = CollisionPlane::none;
  for (int i = 0; i < 3; ++i) {
    // �ړ������ɂ���Ē��ׂ������ς���.
    if (v[i] < 0) { // b�͍��ֈړ���.
      // a���E���ɂ���(���ɗ���Ă���)�ꍇ�͏Փ˂Ȃ�.
      if (bMax[i] < aMin[i]) {
        return { 1, CollisionPlane::none };
      }
      // �Î~��(a)�E�[���ړ���(b)���[���E�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      // ���傫���ق����ՓˊJ�n�����Ƃ��č̗p.
      if (aMax[i] > bMin[i]) {
        const float newTime = (aMax[i] - bMin[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::positiveX, CollisionPlane::positiveY, CollisionPlane::positiveZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // �Î~��(a)���[���ړ���(b)�E�[���E�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      // ��菬�����ق����ՓˏI�������Ƃ��č̗p.
      if (aMin[i] > bMax[i]) {
        tlast = std::min((aMin[i] - bMax[i]) / v[i], tlast);
      }
    } else if (v[i] > 0) { // b�͉E�ֈړ���.
      // a�������ɂ���(���ɗ���Ă���)�ꍇ�͏Փ˂Ȃ�.
      if (bMin[i] > aMax[i]) {
        return { 1, CollisionPlane::none };
      }
      // �Î~��(a)���[���ړ���(b)�E�[��荶�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      if (aMin[i] < bMax[i]) {
        const float newTime = (aMin[i] - bMax[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::negativeX, CollisionPlane::negativeY, CollisionPlane::negativeZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // �Î~��(a)�E�[���ړ���(b)���[��荶�ɂ���(�s���߂��Ă���)�ꍇ�A�ߋ��̏Փˎ������v�Z.
      if (aMax[i] < bMin[i]) {
        tlast = std::min((aMax[i] - bMin[i]) / v[i], tlast);
      }
    }
  }

  if (tfirst > tlast) {
    return { 1, CollisionPlane::none };
  }

  return { tfirst, plane };
}