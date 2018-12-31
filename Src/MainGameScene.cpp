/**
* @file MainGameScene.cpp
*/
#include "MainGameScene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

/**
* 初期化.
*/
bool MainGameScene::Initialize()
{
  random.seed(std::random_device()());

  std::vector<std::string> modelFiles;
  modelFiles.push_back("Res/Tree.obj");
  modelFiles.push_back("Res/House.obj");
  modelFiles.push_back("Res/Rock.obj");
  modelFiles.push_back("Res/Ground.obj");
  modelFiles.push_back("Res/Human.obj");
  modelFiles.push_back("Res/Plane.obj");
  modelFiles.push_back("Res/Bullet.obj");
  if (!meshList.Allocate(modelFiles)) {
    return false;
  }
  progSimple.Reset(Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag"));
  progLighting.Reset(Shader::BuildFromFile("Res/FragmentLighting.vert", "Res/FragmentLighting.frag"));

  // テクスチャを作成する.
  const int imageWidth = 8; // 画像の幅.
  const int imageHeight = 8; // 画像の高さ.
  const GLuint B = 0xff'40'40'40; // 黒.
  const GLuint W = 0xff'ff'ff'ff; // 白.
  const GLuint imageData[imageWidth * imageHeight] = {
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    B, B, B, B, B, B, B, B,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    B, B, B, B, B, B, B, B,
  };
  const GLuint G2 = 0xff'10'80'20;
  const GLuint G1 = 0xff'20'C0'40;
  const GLuint G0 = 0xff'40'E0'80;
  const GLuint R0 = 0xff'20'60'A0;
  const GLuint R1 = 0xff'10'20'60;
  const GLuint imageTree[imageWidth * imageHeight] = {
    R0,R1,R0,R1,R0,R1,R0,R1,
    R0,R0,R0,R0,R0,R0,R0,R0,
    G2,G1,G2,G1,G2,G1,G2,G1,
    G1,G2,G1,G2,G1,G2,G1,G2,
    G1,G1,G2,G1,G1,G1,G2,G1,
    G0,G1,G0,G1,G0,G1,G0,G1,
    G1,G0,G1,G0,G1,G0,G1,G0,
    G0,G0,G0,G0,G0,G0,G0,G0,
  };
  texId.Reset(Texture::CreateImage2D(imageWidth, imageHeight, imageData, GL_RGBA, GL_UNSIGNED_BYTE));
  texTree.Reset(Texture::CreateImage2D(imageWidth, imageHeight, imageTree, GL_RGBA, GL_UNSIGNED_BYTE));
  texHouse.Reset(Texture::LoadImage2D("Res/House.tga"));
  texRock.Reset(Texture::LoadImage2D("Res/Rock.tga"));
  texHuman.Reset(Texture::LoadImage2D("Res/Human.tga"));
  texBullet.Reset(Texture::LoadImage2D("Res/Bullet.tga"));

  texStageClear.Reset(Texture::LoadImage2D("Res/StageClear.tga"));
  texGameOver.Reset(Texture::LoadImage2D("Res/GameOver.tga"));

  // ライトの設定.
  lights.ambient.color = glm::vec3(0.05f, 0.1f, 0.1f);
  lights.directional.direction = glm::normalize(glm::vec3(5, -2, -2));
  lights.directional.color = glm::vec3(1, 1, 1);
  lights.point.position[0] = glm::vec3(5, 4, 0);
  lights.point.color[0] = glm::vec3(1.0f, 0.8f, 0.4f) * 100.0f;
  lights.spot.posAndInnerCutOff[0] = glm::vec4(-6, 6, 8, std::cos(glm::radians(15.0f)));
  lights.spot.dirAndCutOff[0] = glm::vec4(glm::normalize(glm::vec3(-1, -2, -2)), std::cos(glm::radians(20.0f)));
  lights.spot.color[0] = glm::vec3(0.4f, 0.8f, 1.0f) * 200.0f;

  // 視点を設定する.
  viewPos = glm::vec3(20, 30, 30);

  pointLightAngle = 0;

  player.Initialize(4, texHuman.Get(), 10, glm::vec3(8, 0, 8), glm::vec3(0), glm::vec3(1));
  return true;
}

/**
* 入力反映.
*/
void MainGameScene::ProcessInput()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();

  if (state == State::play) {
    // プレイヤーを移動する.
    const float speed = 10.0f;
    player.velocity = glm::vec3(0);
    if (window.IsKeyPressed(GLFW_KEY_A)) {
      player.velocity.x = -1;
    } else if (window.IsKeyPressed(GLFW_KEY_D)) {
      player.velocity.x += 1;
    }
    if (window.IsKeyPressed(GLFW_KEY_W)) {
      player.velocity.z = -1;
    } else if (window.IsKeyPressed(GLFW_KEY_S)) {
      player.velocity.z = 1;
    }
    if (player.velocity.x || player.velocity.z) {
      player.velocity = glm::normalize(player.velocity);

      // ショットボタンが押されていなければ方向転換.
      if (!window.IsKeyPressed(GLFW_KEY_SPACE)) {
        player.rotation.y = glm::acos(player.velocity.x) - 3.14f / 2;
        if (player.velocity.z >= 0) {
          player.rotation.y = 3.14f - player.rotation.y;
        }
      }
      player.velocity *= speed;
    }

    if (window.IsKeyPressed(GLFW_KEY_SPACE)) {
      if (playerShotTimer <= 0) {
        playerShotTimer = 1.0f / 8.0f;
        const glm::mat4 matRotY = glm::rotate(glm::mat4(1), player.rotation.y, glm::vec3(0, 1, 0));
        Actor shot;
        shot.Initialize(6, texBullet.Get(), 1, player.position + glm::vec3(matRotY * glm::vec4(0.25f, 1, -0.125f, 1)), player.rotation, glm::vec3(1));
        shot.velocity = matRotY * glm::vec4(0, 0, -40, 1);
        playerShotList.push_back(shot);
      }
    }

    // ゲームクリア(仮).
    if (window.IsKeyDown(GLFW_KEY_ENTER)) {
      if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT) || window.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT)) {
        state = State::gameOver;
      } else {
        state = State::stageClear;
      }
    }
  } else {
    if (window.IsKeyDown(GLFW_KEY_ENTER)) {
      NextScene("Title");
    }
  }
}

/**
* 状態更新.
*/
void MainGameScene::Update()
{
  const float deltaTime = (float)GLFWEW::Window::Instance().DeltaTime();

  // ゾンビの動き:
  // - 3-8体がまとまって出現する.
  // - 適当に時間を開けて出現させる.
  // - ステージごとに決められた数のゾンビを倒すとクリア.
  // - 出現後はプレイヤーを追いかける.
  // - プレイヤーに近づくと、自分の正面に定期的に攻撃判定を発生させる.
  // - 攻撃判定はプレイヤーに当たると消える.
  // - 攻撃が当たるとプレイヤーはダメージを負う.
  // - プレイヤーの体力が0以下になったらゲームオーバー.

  // ゾンビの移動.
  for (auto& zombie : enemyList) {
    const float moveSpeed = 2.0f;
    const float rotationSpeed = glm::radians(60.0f);
    const float frontRange = glm::radians(15.0f);

    const glm::vec3 v = player.position - zombie.position;
    const glm::vec3 vTarget = glm::normalize(v);
    float radian = std::atan2(-vTarget.z, vTarget.x) - glm::radians(90.0f);
    if (radian <= 0) {
      radian += glm::radians(360.0f);
    }
    const glm::vec3 vZombieFront = glm::rotate(glm::mat4(1), zombie.rotation.y, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 1);
    if (std::abs(radian - zombie.rotation.y) > frontRange) {
      const glm::vec3 vRotDir = glm::cross(vZombieFront, vTarget);
      if (vRotDir.y >= 0) {
        zombie.rotation.y += rotationSpeed * deltaTime;
        if (zombie.rotation.y >= glm::radians(360.0f)) {
          zombie.rotation.y -= glm::radians(360.0f);
        }
      } else {
        zombie.rotation.y -= rotationSpeed * deltaTime;
        if (zombie.rotation.y < 0) {
          zombie.rotation.y += glm::radians(360.0f);
        }
      }
    }
    if (glm::length(v) > 1.0f) {
      zombie.position += vZombieFront * moveSpeed * deltaTime;
    }
  }

  // ゾンビの発生.
  if (enemyLeft > 0) {
    if (enemyPoppingTimer >= 0) {
      enemyPoppingTimer -= deltaTime;
    } else {
      enemyPoppingTimer += 20;

      const int maxPopCount = 10;
      const int popCount = std::min(enemyLeft, maxPopCount);
      enemyLeft -= popCount;

      std::uniform_int_distribution<int> rangeBase(-15, 15);
      std::uniform_int_distribution<int> range(-5, 5);
      glm::vec3 posBase(rangeBase(random), 0, rangeBase(random));
      for (int i = 0; i < popCount; ++i) {
        glm::vec3 pos = posBase + glm::vec3(range(random), 0, range(random));
        Actor zombie;
        zombie.Initialize(4, texHuman.Get(), 10, pos, glm::vec3(0), glm::vec3(1));
        enemyList.push_back(zombie);
      }
    }
  }

  const glm::vec3 viewOffset = glm::vec3(10, 15, 10);
  player.position += player.velocity * deltaTime;
  viewPos = player.position + viewOffset;
  if (playerShotTimer > 0) {
    playerShotTimer -= deltaTime;
  }

  for (auto& e : playerShotList) {
    if (e.health > 0) {
      e.position += e.velocity * deltaTime;
      if (glm::any(glm::lessThan(e.position, glm::vec3(-20)))) {
        e.health = 0;
      } else if (glm::any(glm::greaterThanEqual(e.position, glm::vec3(20)))) {
        e.health = 0;
      }
    }
  }
  playerShotList.erase(std::remove_if(playerShotList.begin(), playerShotList.end(), [](const Actor& e) { return e.health <= 0; }), playerShotList.end());

  // 光源モデルのY軸回転角を更新.
  pointLightAngle += glm::radians(90.0f) * deltaTime;
  if (pointLightAngle > glm::radians(360.0f)) {
    pointLightAngle -= glm::radians(360.0f);
  }
}

/**
* 描画.
*/
void MainGameScene::Render()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // 座標変換行列を作成する.
  const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
  const glm::mat4x4 matView = glm::lookAt(viewPos, player.position, glm::vec3(0, 1, 0));
  progLighting.SetViewProjectionMatrix(matProj * matView);
  progSimple.SetViewProjectionMatrix(matProj * matView);

  progLighting.Use();

  meshList.BindVertexArray();

  // 光源を設定する.
  progLighting.SetLightList(lights);

  progLighting.BindTexture(0, texTree.Get());

  const float treeCount = 10; // 木を植える本数.
  const float radius = 8; //　半径.
  for (float i = 0; i < treeCount; ++i) {
    const float theta = 3.14f * 2 / treeCount * i;
    const float x = std::cos(theta) * radius;
    const float z = std::sin(theta) * radius;
    progLighting.Draw(meshList[0], glm::vec3(x, 0, z), glm::vec3(0, theta * 5, 0), glm::vec3(1));
  }

  progLighting.BindTexture(0, texId.Get());
  progLighting.Draw(meshList[3], glm::vec3(0), glm::vec3(0), glm::vec3(1));

  progLighting.BindTexture(0, texHouse.Get());
  progLighting.Draw(meshList[1], glm::vec3(0), glm::vec3(0), glm::vec3(1));
  progLighting.Draw(meshList[1], glm::vec3(0, 0, 15), glm::vec3(0), glm::vec3(1));
  progLighting.Draw(meshList[1], glm::vec3(0, 0, -15), glm::vec3(0), glm::vec3(1));

  progLighting.BindTexture(0, texRock.Get());
  progLighting.Draw(meshList[2], glm::vec3(4, 0, 0), glm::vec3(0), glm::vec3(1));

  progLighting.BindTexture(0, player.texture);
  progLighting.Draw(meshList[player.mesh], player.position, player.rotation, player.scale);

  for (const auto& e : enemyList) {
    if (e.health > 0) {
      progLighting.BindTexture(0, e.texture);
      progLighting.Draw(meshList[e.mesh], e.position, e.rotation, e.scale);
    }
  }

  for (const auto& e : playerShotList) {
    if (e.health > 0) {
      progLighting.BindTexture(0, e.texture);
      progLighting.Draw(meshList[e.mesh], e.position, e.rotation, e.scale);
    }
  }

  // ポイント・ライトの位置が分かるように適当なモデルを表示.
  progSimple.Use();
  progSimple.BindTexture(0, texId.Get());
  for (int i = 0; i < 8; ++i) {
    progSimple.Draw(meshList[4], lights.point.position[i], glm::vec3(0, pointLightAngle, 0), glm::vec3(1.0f, -0.25f, 1.0f));
  }

  {
    const glm::mat4x4 matProj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
    const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    progSimple.SetViewProjectionMatrix(matProj * matView);
    if (state == State::stageClear) {
      progSimple.BindTexture(0, texStageClear.Get());
      progSimple.Draw(meshList[5], glm::vec3(0), glm::vec3(0), glm::vec3(350, 60, 1));
    } else if (state == State::gameOver) {
      progSimple.BindTexture(0, texGameOver.Get());
      progSimple.Draw(meshList[5], glm::vec3(0), glm::vec3(0), glm::vec3(300, 60, 1));
    }
  }
}

/**
* 終了.
*/
void MainGameScene::Finalize()
{
}
