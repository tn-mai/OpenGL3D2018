/**
* @file MainGameScene.h
*/
#ifndef MAINGAMESCENE_H_INCLUDED
#define MAINGAMESCENE_H_INCLUDED
#include "GLFWEW.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshList.h"

/**
* メインゲームシーン.
*/
class MainGameScene
{
public:
  MainGameScene() = default;
  ~MainGameScene() = default;

  bool Initialize();
  void ProcessInput();
  void Update();
  void Render();
  void Finalize();

private:
  MeshList meshList;

  Texture::Image2D texId;
  Texture::Image2D texTree;
  Texture::Image2D texHouse;
  Texture::Image2D texRock;
  Texture::Image2D texHuman;

  Shader::Program progSimple;
  Shader::Program progLighting;
  Shader::LightList lights;

  glm::vec3 viewPos;
  float pointLightAngle;
};

#endif // MAINGAMESCENE_H_INCLUDED