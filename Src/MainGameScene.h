/**
* @file MainGameScene.h
*/
#ifndef MAINGAMESCENE_H_INCLUDED
#define MAINGAMESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"
#include "Scene.h"
#include "Actor.h"
#include <random>

/**
* メインゲーム画面.
*/
class MainGameScene : public Scene
{
public:
  MainGameScene() = default;
  virtual ~MainGameScene() = default;

  virtual bool Initialize() override;
  virtual void ProcessInput() override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Finalize() override;

private:
  MeshList meshList;

  Texture::Image2D texId;
  Texture::Image2D texTree;
  Texture::Image2D texHouse;
  Texture::Image2D texRock;
  Texture::Image2D texHuman;
  Texture::Image2D texStageClear;
  Texture::Image2D texGameOver;
  Texture::Image2D texBullet;

  Shader::Program progSimple;
  Shader::Program progLighting;
  Shader::LightList lights;

  glm::vec3 viewPos;
  float pointLightAngle;

  enum class State {
    play,
    stageClear,
    gameOver,
  };
  State state = State::play;

  std::mt19937 random;

  PlayerActor player;
  std::vector<Actor*> playerBulletList;
  std::vector<Actor*> enemyList;
  std::vector<Actor*> objectList;

  float playerBulletTimer = 0;

  int stageNo = 1;
  float enemySpeed = 1.0f; // ゾンビの移動速度.
  float enemyPoppingInterval = 15.0f;
  float enemyPoppingTimer = 0.0f;

  int enemyTotal = 100; // 敵の総数.
  int enemyLeft = 100; // 未登場の敵の数. 敵を出現させるたびに減少していく.
  int enemyKilled = 0; // 殺した敵の数. この数値がenemyTotalと等しくなったらステージクリア.
};

#endif // MAINGAMESCENE_H_INCLUDED