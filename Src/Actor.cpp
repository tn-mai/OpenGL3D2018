/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>

/**
* 初期化.
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
* 終了.
*/
void Actor::Finalize()
{
}

/**
* 更新.
*/
void Actor::Update()
{
  colWorld.origin = colLocal.origin + position;
  colWorld.size = colLocal.size;
}


/**
* 利用可能なのActorを取得する.
*
* @param first 検索対象の先頭要素のポインタ.
* @param last  検索対象の終端要素のポインタ.
*
* @return 利用可能なActorのポインタ.
*         利用可能なActorが見つからなければnullptr.
*
* ActorListから、利用可能な(healthが0以下の)Actorを検索する.
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
* 2つの長方形の衝突状態を調べる.
*
* @param lhs 長方形その1.
* @param rhs 長方形その2.
*
* @retval true  衝突している.
* @retval false 衝突していない.
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