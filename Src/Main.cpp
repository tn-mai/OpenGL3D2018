/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "MainGameScene.h"

/// エントリーポイント.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL Tutorial")) {
    return 1;
  }

  MainGameScene mainGameScene;
  if (!mainGameScene.Initialize()) {
    return 1;
  }

  // メインループ.
  window.InitTimer();
  while (!window.ShouldClose()) {
    window.UpdateTimer();
    mainGameScene.ProcessInput();
    mainGameScene.Update();
    mainGameScene.Render();
    window.SwapBuffers();
  }
  mainGameScene.Finalize();

  return 0;
}
