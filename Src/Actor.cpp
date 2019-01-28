/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

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
    if (actor) {
      actor->Finalize();
      delete actor;
    }
  }
  actorList.clear();
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