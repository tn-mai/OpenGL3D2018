/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "MainGameScene.h"
#include "TitleScene.h"
#include <memory>

/// エントリーポイント.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL Tutorial")) {
    return 1;
  }

  std::shared_ptr<Scene> pScene (new TitleScene);
  if (!pScene->Initialize()) {
    return 1;
  }

  // メインループ.
  window.InitTimer();
  while (!window.ShouldClose()) {
    window.Update();

    // シーンを切り替える.
    if (!pScene->NextScene().empty()) {
      glFinish();
      pScene->Finalize();
      if (pScene->NextScene() == "Title") {
        pScene.reset(new TitleScene);
      } else if (pScene->NextScene() == "MainGame") {
        pScene.reset(new MainGameScene);
      }
      if (!pScene->Initialize()) {
        return 1;
      }
      window.InitTimer();
    }

    pScene->ProcessInput();
    pScene->Update();
    pScene->Render();
    window.SwapBuffers();
  }
  pScene->Finalize();

  return 0;
}
