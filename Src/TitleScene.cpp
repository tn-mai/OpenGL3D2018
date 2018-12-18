/**
* @file TitleScene.h
*/
#include "TitleScene.h"
#include <glm/gtc/matrix_transform.hpp>

/**
* 初期化.
*/
bool TitleScene::Initialize()
{
  std::vector<std::string> modelList;
  modelList.push_back("Res/Plane.obj");
  if (!meshList.Allocate(modelList)) {
    return false;
  }

  progSimple.Reset(Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag"));

  texLogo.Reset(Texture::LoadImage2D("Res/TitleLogo.tga"));
  texBackGround.Reset(Texture::LoadImage2D("Res/TItleBack.tga"));

  return true;
}

/**
* 入力の処理.
*/
void TitleScene::ProcessInput()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (window.IsKeyDown(GLFW_KEY_ENTER)) {
    NextScene("MainGame");
  }
}

/**
* 状態の更新.
*/
void TitleScene::Update()
{
  // 座標変換行列を作成する.
//  const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
  const glm::mat4x4 matProj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 1.0f, 500.0f);
  const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  progSimple.SetViewProjectionMatrix(matProj * matView);
}

/**
* 描画.
*/
void TitleScene::Render()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  progSimple.Use();

  meshList.BindVertexArray();

  progSimple.BindTexture(0, texBackGround.Get());
  progSimple.Draw(meshList[0], glm::vec3(400, 300, -1), glm::vec3(0), glm::vec3(400, 300, 1));

  progSimple.BindTexture(0, texLogo.Get());
  progSimple.Draw(meshList[0], glm::vec3(400, 300, 0), glm::vec3(0), glm::vec3(400, 300, 1));
}

/**
* 終了.
*/
void TitleScene::Finalize()
{
}

