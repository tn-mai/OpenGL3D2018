/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>

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
*/
void Actor::Update()
{
  colWorld.origin = colLocal.origin + position;
  colWorld.size = colLocal.size;
}


/**
* ���p�\�Ȃ�Actor���擾����.
*
* @param first �����Ώۂ̐擪�v�f�̃|�C���^.
* @param last  �����Ώۂ̏I�[�v�f�̃|�C���^.
*
* @return ���p�\��Actor�̃|�C���^.
*         ���p�\��Actor��������Ȃ����nullptr.
*
* ActorList����A���p�\��(health��0�ȉ���)Actor����������.
*/
Actor* FindAvailableActor(Actor* first, Actor* last)
{
  for (Actor* i = first; i != last; ++i) {
    if (i->health <= 0) {
      return i;
    }
  }
  return nullptr;
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

CollidePoint FindCollidePoint(const Actor& lhs, const Actor& rhs, float deltaTime)
{
  const glm::vec3 lmin = lhs.colWorld.origin;
  const glm::vec3 lmax = lmin + lhs.colWorld.size;
  const glm::vec3 rmin = rhs.colWorld.origin;
  const glm::vec3 rmax = rmin + rhs.colWorld.size;
  const glm::vec3 v = (rhs.velocity - lhs.velocity) * deltaTime;
  float tfirst = 0.0f;
  float tlast = 1.0f;
  for (int i = 0; i < 3; ++i) {
    if (v[i] < 0) {
      if (rmax[i] < lmin[i]) {
        return { false };
      }
      if (lmax[i] < rmin[i]) {
        tfirst = std::max((lmax[i] - rmin[i]) / v[i], tfirst);
      }
      if (rmax[i] > lmin[i]) {
        tlast = std::min((lmin[i] - rmax[i]) / v[i], tlast);
      }
    } else if (v[i] > 0) {
      if (rmin[i] > lmax[i]) {
        return { false };
      }
      if (rmax[i] < lmin[i]) {
        tfirst = std::max((lmin[i] - rmax[i]) / v[i], tfirst);
      }
      if (lmax[i] > rmin[i]) {
        tlast = std::min((lmax[i] - rmin[i]) / v[i], tlast);
      }
    }
  }

  if (tfirst > tlast) {
    return { false };
  }

  return { true, rhs.position + v * tfirst };
}