/**
* @file Actor.cpp
*/
#include "Actor.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
*
* @param deltaTime 経過時間.
*/
void Actor::Update(float deltaTime)
{
  position += velocity * deltaTime;
  colWorld.origin = colLocal.origin + position;
  colWorld.size = colLocal.size;
}

/**
* 利用可能なActorを取得する.
*
* @param actorList 検索対象のアクターのリスト.
*
* @return 利用可能なActorのポインタ.
*         利用可能なActorが見つからなければnullptr.
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
* アクターの状態を更新する.
*
* @param actorList 更新するアクターのリスト.
* @param deltaTime 前回の更新からの経過時間.
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
* Actorを描画する.
*
* @param actorList 描画するアクターのリスト.
* @param shader    描画に使用するシェーダー・オブジェクト.
* @param meshList  描画に使用するメッシュリスト.
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
* アクターリストを空にする.
*
* @param actorList 空にするアクターのリスト.
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

  // 十分に接近していなければ移動する. 接近していれば攻撃する.
  if (glm::length(v) > 1.0f) {
    velocity = vZombieFront * moveSpeed;
  } else {
    velocity = glm::vec3(0);
    // 定期的に攻撃状態になる.
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

/**
* 衝突するまでの経過時間を計算する.
*/
CollisionTime FindCollisionTime(const Actor& a, const Actor& b, float deltaTime)
{
  const glm::vec3 aMin = a.colWorld.origin;
  const glm::vec3 aMax = aMin + a.colWorld.size;
  const glm::vec3 bMin = b.colWorld.origin;
  const glm::vec3 bMax = bMin + b.colWorld.size;

  // アクターaが静止、アクターbが移動しているとみなし、衝突が起こった最短時刻を調べる.
  const glm::vec3 v = (b.velocity - a.velocity) * deltaTime;
  float tfirst = -1.0f;
  float tlast = 0.0f;
  CollisionPlane plane = CollisionPlane::none;
  for (int i = 0; i < 3; ++i) {
    // 移動方向によって調べる向きを変える.
    if (v[i] < 0) { // bは左へ移動中.
      // aが右側にある(既に離れている)場合は衝突なし.
      if (bMax[i] < aMin[i]) {
        return { 1, CollisionPlane::none };
      }
      // 静止側(a)右端が移動側(b)左端より右にある(行き過ぎている)場合、過去の衝突時刻を計算.
      // より大きいほうを衝突開始時刻として採用.
      if (aMax[i] > bMin[i]) {
        const float newTime = (aMax[i] - bMin[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::positiveX, CollisionPlane::positiveY, CollisionPlane::positiveZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // 静止側(a)左端が移動側(b)右端より右にある(行き過ぎている)場合、過去の衝突時刻を計算.
      // より小さいほうを衝突終了時刻として採用.
      if (aMin[i] > bMax[i]) {
        tlast = std::min((aMin[i] - bMax[i]) / v[i], tlast);
      }
    } else if (v[i] > 0) { // bは右へ移動中.
      // aが左側にある(既に離れている)場合は衝突なし.
      if (bMin[i] > aMax[i]) {
        return { 1, CollisionPlane::none };
      }
      // 静止側(a)左端が移動側(b)右端より左にある(行き過ぎている)場合、過去の衝突時刻を計算.
      if (aMin[i] < bMax[i]) {
        const float newTime = (aMin[i] - bMax[i]) / v[i];
        if (newTime > tfirst) {
          const CollisionPlane planes[] = { CollisionPlane::negativeX, CollisionPlane::negativeY, CollisionPlane::negativeZ };
          plane = planes[i];
          tfirst = newTime;
        }
      }
      // 静止側(a)右端が移動側(b)左端より左にある(行き過ぎている)場合、過去の衝突時刻を計算.
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