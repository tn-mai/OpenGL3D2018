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
  texHP.Reset(Texture::LoadImage2D("Res/HP.tga"));
  texDay.Reset(Texture::LoadImage2D("Res/Day.tga"));
  texScore.Reset(Texture::LoadImage2D("Res/Score.tga"));
  for (int i = 0; i < 10; ++i) {
    std::string filename = "Res/Number_";
    filename += '0' + i;
    filename += ".tga";
    texNumber[i].Reset(Texture::LoadImage2D(filename.c_str()));
  }

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
  player.colLocal = { {-0.5f, 0, -0.5f }, {1, 1.7f, 1} };
  playerBulletList.resize(128);
  for (auto& e : playerBulletList) {
    e = new BulletActor;
  }

  enemyList.resize(128);
  for (auto& e : enemyList) {
    e = new ZombieActor;
  }

  objectList.resize(128);
  for (auto& e : objectList) {
    e = new Actor;
  }

  const int treeCount = 10; // 木を植える本数.
  const float radius = 8; //　半径.
  for (float i = 0; i < treeCount; ++i) {
    const float theta = 3.14f * 2 / treeCount * i;
    const float x = std::cos(theta) * radius;
    const float z = std::sin(theta) * radius;
    objectList[(size_t)i]->Initialize(0, texTree.Get(), 1, glm::vec3(x, 0, z), glm::vec3(0, theta * 5, 0), glm::vec3(1));
    objectList[(size_t)i]->colLocal = { {-0.5f, 0, -0.5f }, { 1, 4, 1 } };
    objectList[(size_t)i]->Update(0);
  }
  objectList[treeCount + 0]->Initialize(1, texHouse.Get(), 1, glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1));
  objectList[treeCount + 0]->colLocal = { {-3, 0, -3 }, { 6, 4, 6 } };
  objectList[treeCount + 0]->Update(0);
  objectList[treeCount + 1]->Initialize(1, texHouse.Get(), 1, glm::vec3(0, 0, -15), glm::vec3(0), glm::vec3(1));
  objectList[treeCount + 1]->colLocal = { {-3, 0, -3 }, { 6, 4, 6 } };
  objectList[treeCount + 1]->Update(0);
  objectList[treeCount + 2]->Initialize(1, texHouse.Get(), 1, glm::vec3(0, 0, 15), glm::vec3(0), glm::vec3(1));
  objectList[treeCount + 2]->colLocal = { {-3, 0, -3 }, { 6, 4, 6 } };
  objectList[treeCount + 2]->Update(0);

  objectList[treeCount + 3]->Initialize(2, texRock.Get(), 1, glm::vec3(4, 0, 0), glm::vec3(0), glm::vec3(1));
  objectList[treeCount + 3]->colLocal = { {-0.5f, 0, -0.5f }, { 1, 1, 1 } };
  objectList[treeCount + 3]->Update(0);

  objectList[treeCount + 4]->Initialize(3, texId.Get(), 1, glm::vec3(0, 0, 0), glm::vec3(0), glm::vec3(1));

  enemyTotal = 20;
  enemyLeft = enemyTotal;
  enemyKilled = 0;

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
        player.direction = glm::acos(player.velocity.x) - 3.14f / 2;
        if (player.velocity.z >= 0) {
          player.direction = 3.14f - player.direction;
        }
      }
      player.velocity *= speed;
    }

    if (window.IsKeyPressed(GLFW_KEY_SPACE)) {
      if (playerBulletTimer <= 0) {
        playerBulletTimer = 1.0f / 8.0f;
        const glm::mat4 matRotY = glm::rotate(glm::mat4(1), player.direction, glm::vec3(0, 1, 0));
        Actor* bullet = FindAvailableActor(playerBulletList);
        if (bullet) {
          bullet->Initialize(6, texBullet.Get(), 1, player.position + glm::vec3(matRotY * glm::vec4(0.25f, 1, -0.125f, 1)), player.rotation, glm::vec3(1));
          bullet->colLocal = { glm::vec3(-0.25f, -0.25f, -0.25f), glm::vec3(1, 1, 1) };
          bullet->velocity = matRotY * glm::vec4(0, 0, -40, 1);
        }
      }
    }
  } else if (state == State::stageClear) {
    player.velocity.x = player.velocity.z = 0;
    if (window.IsKeyDown(GLFW_KEY_ENTER)) {
      ++stageNo;
      enemyTotal = 10 + stageNo * 10;
      enemyLeft = enemyTotal;
      enemyKilled = 0;
      enemySpeed = 1.0f + (float)(stageNo - 1) * 0.1f;
      enemyPoppingInterval = 15.0f - (float)(stageNo - 1) * 1.0f;
      enemyPoppingTimer = 0;
      player.position = glm::vec3(8, 0, 8);
      state = State::play;
    }
  } else {
    player.velocity.x = player.velocity.z = 0;
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

  // ゲームの目的:
  // - 無限に湧いてくるゾンビを倒し続ける.
  // - 規定数を倒すとステージクリア.
  // - ステージごとに決められた数のゾンビを倒すとクリア.
  // - ステージが進むと出現するゾンビの総数、同時発生数が増え、移動速度が上がる.
  // - プレイヤーの体力が0以下になったらゲームオーバー.

  // ゾンビの動き:
  // - マップを10m四方に区切り、その中のランダムに選ばれた区域に出現.
  // - (ステージ数*2+0～3)体がまとまって出現する.
  // - 出現間隔は(30-ステージ数*2)秒. ただし10秒未満にはならない.
  // - 出現後はプレイヤーを追いかける.
  // - プレイヤーに近づくと、自分の正面に定期的に攻撃判定を発生させる.
  // - 攻撃判定は1フレームだけ.
  // - 攻撃が当たるとプレイヤーはダメージを負う.

  // プレイヤーの更新.
  player.Update(deltaTime);
  for (auto& object : objectList) {
    if (object->health > 0) {
      if (DetectCollision(player, *object)) {
        const CollisionTime t = FindCollisionTime(*object, player, deltaTime);
        if (t.plane != CollisionPlane::none) {
          const float time = deltaTime * t.time - 0.00001f;
          player.position += player.velocity * time;
          if (t.plane == CollisionPlane::negativeX || t.plane == CollisionPlane::positiveX) {
            player.velocity.x = 0;
          } else if (t.plane == CollisionPlane::negativeY || t.plane == CollisionPlane::positiveY) {
            player.velocity.y = 0;
          } else if (t.plane == CollisionPlane::negativeZ || t.plane == CollisionPlane::positiveZ) {
            player.velocity.z = 0;
          }
          player.velocity *= -t.time;
          player.position += player.velocity * -time;
        }
      }
    }
  }

  // 自機ショットの更新.
  UpdateActorList(playerBulletList, deltaTime);

  // ゾンビの更新.
  UpdateActorList(enemyList, deltaTime);

  // ゾンビの発生.
  if (enemyLeft > 0) {
    if (enemyPoppingTimer >= 0) {
      enemyPoppingTimer -= deltaTime;
    } else {
      enemyPoppingTimer += enemyPoppingInterval;

      const int maxPopCount = 10;
      const int popCount = std::min(enemyLeft, maxPopCount);
      enemyLeft -= popCount;

      std::uniform_int_distribution<int> rangeBase(-15, 15);
      std::uniform_int_distribution<int> range(-5, 5);
      glm::vec3 posBase(rangeBase(random), 0, rangeBase(random));
      for (int i = 0; i < popCount; ++i) {
        glm::vec3 pos = posBase + glm::vec3(range(random), 0, range(random));
        ZombieActor* zombie = (ZombieActor*)FindAvailableActor(enemyList);
        if (zombie) {
          zombie->Initialize(4, texHuman.Get(), 5, pos, glm::vec3(0), glm::vec3(1));
          zombie->colLocal = { glm::vec3(-0.5f, 0, -0.5f), glm::vec3(1, 1.8f, 1) };
          zombie->target = &player;
          zombie->baseSpeed = enemySpeed;
        }
      }
    }
  }

  // カメラの更新.
  const glm::vec3 viewOffset = glm::vec3(0, 15, 10);
  viewPos = player.position + viewOffset;

  // プレイヤーの弾の発射タイマーの更新.
  if (playerBulletTimer > 0) {
    playerBulletTimer -= deltaTime;
  }

  // プレイヤーの弾と敵の衝突判定.
  for (auto& bullet : playerBulletList) {
    if (bullet->health <= 0) {
      continue;
    }
    for (auto& zombie : enemyList) {
      if (zombie->health <= 0) {
        continue;
      }
      if (DetectCollision(*bullet, *zombie)) {
        const CollisionTime t = FindCollisionTime(*bullet, *zombie, deltaTime);
        if (t.time) {
          zombie->health -= bullet->health;
          bullet->health = 0;
          if (zombie->health <= 0) {
            score += 200;
            ++enemyKilled;
          } else {
            score += 10;
          }
          break;
        }
      }
    }
    bullet->position += bullet->velocity * deltaTime;
  }

  // 敵をすべて倒したらステージクリア.
  if (enemyKilled == enemyTotal) {
    state = State::stageClear;
  }

  // ゾンビの攻撃.
  for (auto& actor : enemyList) {
    if (actor->health <= 0) {
      continue;
    }
    ZombieActor* zombie = (ZombieActor*)actor;
    if (zombie->target->health <= 0) {
      continue;
    }
    if (zombie->isAttacking) {
      const glm::vec3 vFront = glm::rotate(glm::mat4(1), zombie->rotation.y, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -1, 0);
      const glm::vec3 vTarget = zombie->target->position - zombie->position;
      const float angle = std::acos(glm::dot(vFront, vTarget));
      if (std::abs(angle) < glm::radians(45.0f) && glm::length(vTarget) < 1.5f) {
        --zombie->target->health;
      }
    }
  }

  // プレイヤーの体力が0以下になったらゲームオーバー.
  if (player.health <= 0) {
    state = State::gameOver;
  }

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

  progLighting.BindTexture(0, player.texture);
  progLighting.Draw(meshList[player.mesh], player.position, player.rotation, player.scale);

  RenderActorList(objectList, progLighting, meshList);
  RenderActorList(enemyList, progLighting, meshList);
  RenderActorList(playerBulletList, progLighting, meshList);

  // ポイント・ライトの位置が分かるように適当なモデルを表示.
  progSimple.Use();
  progSimple.BindTexture(0, texId.Get());
  for (int i = 0; i < 8; ++i) {
    progSimple.Draw(meshList[4], lights.point.position[i], glm::vec3(0, pointLightAngle, 0), glm::vec3(1.0f, -0.25f, 1.0f));
  }

  {
    glDisable(GL_DEPTH_TEST);

    const glm::mat4x4 matProj = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 500.0f);
    const glm::mat4x4 matView = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    progSimple.SetViewProjectionMatrix(matProj * matView);

    // ステージ数表示.
    progSimple.BindTexture(0, texDay.Get());
    progSimple.Draw(meshList[5], glm::vec3(-336, -300 + 64 + 24 + 4, 0), glm::vec3(0), glm::vec3(256 / 4, 128 / 4, 1));
    int tmpStageNo = stageNo;
    if (tmpStageNo > 999) {
      tmpStageNo = 999;
    }
    for (int i = 0; i < 3; ++i) {
      const int number = tmpStageNo % 10;
      progSimple.BindTexture(0, texNumber[number].Get());
      progSimple.Draw(meshList[5], glm::vec3(-300 + 32 * (3 - i), -300 + 64 + 24 + 4, 0), glm::vec3(0), glm::vec3(32, 32, 1));
      tmpStageNo /= 10;
    }

    // HP表示.
    progSimple.BindTexture(0, texHP.Get());
    progSimple.Draw(meshList[5], glm::vec3(-336, -300 + 24 + 4, 0), glm::vec3(0), glm::vec3(192 / 4, 128 / 4, 1));
    int tmpHealth = player.health;
    if (tmpHealth < 0) {
      tmpHealth = 0;
    } else if (tmpHealth > 99) {
      tmpHealth = 99;
    }
    for (int i = 0; i < 2; ++i) {
      const int number = tmpHealth % 10;
      progSimple.BindTexture(0, texNumber[number].Get());
      progSimple.Draw(meshList[5], glm::vec3(-300 + 32 * (2 - i), -300 + 24 + 4, 0), glm::vec3(0), glm::vec3(32, 32, 1));
      tmpHealth /= 10;
    }

    // スコア表示.
    progSimple.BindTexture(0, texScore.Get());
    progSimple.Draw(meshList[5], glm::vec3(-120, 300 - 24 - 4, 0), glm::vec3(0), glm::vec3(384 / 4, 128 / 4, 1));
    int tmpScore = score;
    if (tmpScore > 99999999) {
      tmpScore = 99999999;
    }
    for (int i = 0; i < 8; ++i) {
      const int number = tmpScore % 10;
      progSimple.BindTexture(0, texNumber[number].Get());
      progSimple.Draw(meshList[5], glm::vec3(-32 + 32 * (8 - i), 300 - 24 - 4, 0), glm::vec3(0), glm::vec3(32, 32, 1));
      tmpScore /= 10;
    }

    // ステージクリア・ゲームオーバー表示.
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
  ClearActorList(playerBulletList);
  ClearActorList(enemyList);
  ClearActorList(objectList);
}
