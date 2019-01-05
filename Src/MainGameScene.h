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

  Actor player;
  float playerShotTimer = 0;
  ActorList playerShotList;

  std::mt19937 random;

  float enemyPoppingTimer = 0;
  int enemyLeft = 100;
  ActorList enemyList;
};

#endif // MAINGAMESCENE_H_INCLUDED