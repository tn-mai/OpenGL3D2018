/**
* @file Main.cpp
*/
#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include "Geometry.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

/// 頂点データ.
const Vertex vertices[] = {
  // 木
  { { 0.00f, 5.0f, 0.00f}, {0.5f, 0.8f, 0.3f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 1.5f,-1.10f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.75f, 1.5f, 0.40f}, {0.1f, 0.3f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },
  { { 0.00f, 4.0f, 0.00f}, {0.2f, 0.1f, 0.0f, 1.0f}, { 0.0f, 0.0f }, { 0.00f, 1.00f, 0.00f } },
  { { 0.00f, 0.0f,-0.37f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.00f,-0.49f,-0.87f } },
  { {-0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, {-0.76f,-0.49f, 0.43f } },
  { { 0.25f, 0.0f, 0.13f}, {0.5f, 0.3f, 0.2f, 1.0f}, { 0.0f, 0.0f }, { 0.76f,-0.49f, 0.43f } },

  // 家
  { { 2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 1.000f, 0.00f }, { 0.71f, 0.0f, 0.71f } },
  { { 3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 1.000f, 0.69f }, { 0.71f, 0.0f, 0.71f } },
  { { 0.0f, 6.0f, 3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.875f, 1.00f }, { 0.00f, 0.0f, 1.00f } },
  { {-3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.750f, 0.69f }, {-0.71f, 0.0f, 0.71f } },
  { {-2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.750f, 0.00f }, {-0.71f, 0.0f, 0.71f } },

  { {-2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.500f, 0.00f }, {-0.71f, 0.0f,-0.71f } },
  { {-3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.500f, 0.69f }, {-0.71f, 0.0f,-0.71f } },
  { { 0.0f, 6.0f,-3.0f}, {0.5f, 0.4f, 0.2f, 1.0f}, { 0.375f, 1.00f }, { 0.00f, 0.0f,-1.00f } },
  { { 3.0f, 4.0f,-3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.250f, 0.69f }, { 0.71f, 0.0f,-0.71f } },
  { { 2.8f, 0.0f,-3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.250f, 0.00f }, { 0.71f, 0.0f,-0.71f } },

  { { 2.8f, 0.0f, 3.0f}, {0.4f, 0.3f, 0.2f, 1.0f}, { 0.000f, 0.00f }, { 0.71f, 0.0f, 0.71f } },
  { { 3.0f, 4.0f, 3.0f}, {0.6f, 0.5f, 0.3f, 1.0f}, { 0.000f, 0.69f }, { 0.71f, 0.0f, 0.71f } },

  { { 0.0f, 6.0f, 3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.750f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f,-3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.500f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f,-3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.250f, 1.00f }, { 0.00f, 1.0f, 0.00f } },
  { { 0.0f, 6.0f, 3.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, { 0.000f, 1.00f }, { 0.00f, 1.0f, 0.00f } },

  // 岩
  { { 0.4f, 0.4f, 0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.5f, 0.0f }, { 0.58f, 0.58f, 0.58f } },
  { { 0.4f, 0.5f,-0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.5f, 0.5f }, { 0.58f, 0.58f,-0.58f } },
  { {-0.4f, 0.6f,-0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.0f, 0.5f }, {-0.58f, 0.58f,-0.58f } },
  { {-0.4f, 0.4f, 0.4f}, {0.2f, 0.2f, 0.2f, 1.0f}, { 0.0f, 0.0f }, {-0.58f, 0.58f, 0.58f } },

  { { 0.3f, 0.0f, 0.7f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 1.0f, 0.0f }, { 0.71f, 0.0f, 0.71f } },
  { { 0.7f, 0.0f,-0.3f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 1.0f, 1.0f }, { 0.71f, 0.0f,-0.71f } },
  { {-0.3f, 0.0f,-0.7f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 0.0f, 1.0f }, {-0.71f, 0.0f,-0.71f } },
  { {-0.7f, 0.0f, 0.3f}, {0.3f, 0.3f, 0.3f, 1.0f}, { 0.0f, 0.0f }, {-0.71f, 0.0f, 0.71f } },

  // 地面
  { {-20.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 5.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f, 20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f, 0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 0.0f, 5.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f, 0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 5.0f, 5.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f, 0.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 5.0f }, { 0.0f, 1.0f, 0.0f } },

  { {-20.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 0.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { {  0.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 5.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
  { { 20.0f, 0.0f,-20.0f}, {0.8f, 0.8f, 0.8f, 1.0f}, { 10.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },

  // 未使用
  { {-0.25f,  0.0f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.25f,  0.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { { 0.0f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },

  { {-0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.0f,  0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { {-0.25f,  0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },

  { { 0.0f,  0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f} },
  { { 0.5f,  0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} },
  { { 0.25f,  0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} },
};

/// インデックスデータ.
const GLushort indices[] = {
  // 木
  0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
  4, 5, 6, 4, 6, 7, 4, 7, 5,

  // 家
  0, 1, 3, 3, 4, 0, 1, 2, 3,
  5, 6, 8, 8, 9, 5, 6, 7, 8,
  9, 8, 11, 11, 10, 9,
  4, 3, 6, 6, 5, 4,
  3, 12, 13, 13, 6, 3,
  8, 14, 15, 15, 11, 8,

  // 石
  0, 1, 2, 2, 3, 0,
  4, 5, 1, 1, 0, 4,
  5, 6, 2, 2, 1, 5,
  6, 7, 3, 3, 2, 6,
  7, 4, 0, 0, 3, 7,

  // 地面
  0, 1, 4, 4, 3, 0, 1, 2, 5, 5, 4, 1,
  3, 4, 7, 7, 6, 3, 4, 5, 8, 8, 7, 4,

  12, 13, 16, 13, 14, 16, 14, 15, 16, 15, 12, 16,
  13, 12, 17, 14, 13, 17, 15, 14, 17, 12, 15, 17,

  0, 1, 2, 2, 3, 0,
  4, 5, 6, 7, 8, 9,
};

/**
* メッシュ配列.
*/
const Mesh meshList[] = {
  { GL_TRIANGLES, 3 * 7, (const GLvoid*)0, 0 },
  { GL_TRIANGLES, 3 * 14, (const GLvoid*)(21 * sizeof(indices[0])), 8 },
  { GL_TRIANGLES, 3 * 10, (const GLvoid*)(63 * sizeof(indices[0])), 24 },
  { GL_TRIANGLES, 24, (const GLvoid*)(93 * sizeof(indices[0])), 32 },
};

/// 頂点シェーダ.
static const char* vsCode =
"#version 410 \n"
"layout(location=0) in vec3 vPosition; \n"
"layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexCoord; \n"
"layout(location=0) out vec4 outColor; \n"
"layout(location=1) out vec2 outTexCoord; \n"
"uniform mat4x4 matMVP; \n"
"void main() { \n"
"  outColor = vColor; \n"
"  outTexCoord = vTexCoord; \n"
"  gl_Position = matMVP * vec4(vPosition, 1.0); \n"
"} \n";

/// フラグメントシェーダ.
static const char* fsCode =
"#version 410 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexCoord; \n"
"out vec4 fragColor; \n"
"uniform sampler2D texColor; \n"
"void main() { \n"
"  fragColor = inColor * texture(texColor, inTexCoord); \n"
"} \n";

/**
* Vertex Buffer Objectを作成する.
*
* @param size 頂点データのサイズ.
* @param data 頂点データへのポインタ.
*
* @return 作成したVBO.
*/
GLuint CreateVBO(GLsizeiptr size, const GLvoid* data)
{
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  return vbo;
}

/**
* Index Buffer Objectを作成する.
*
* @param size インデックスデータのサイズ.
* @param data インデックスデータへのポインタ.
*
* @return 作成したIBO.
*/
GLuint CreateIBO(GLsizeiptr size, const GLvoid* data)
{
  GLuint ibo = 0;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  return ibo;
}

/**
* Vertex Array Objectを作成する.
*
* @param vbo VAOに関連付けられるVBO.
* @param ibo VAOに関連付けられるIBO.
*
* @return 作成したVAO.
*/
GLuint CreateVAO(GLuint vbo, GLuint ibo)
{
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  const GLsizei stride = sizeof(Vertex);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, position)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, color)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, texCoord)));
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, sizeof(Vertex::normal) / sizeof(float), GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offsetof(Vertex, normal)));
  glBindVertexArray(0);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);
  return vao;
}

/// エントリーポイント.
int main()
{
  GLFWEW::Window& window = GLFWEW::Window::Instance();
  if (!window.Init(800, 600, "OpenGL Tutorial")) {
    return 1;
  }

  const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
  const GLuint ibo = CreateIBO(sizeof(indices), indices);
  const GLuint vao = CreateVAO(vbo, ibo);
  const GLuint shaderProgram = Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag");
  const GLuint fragmentLightingId = Shader::BuildFromFile("Res/FragmentLighting.vert", "Res/FragmentLighting.frag");
  if (!vbo || !ibo || !vao || !shaderProgram || !fragmentLightingId) {
    return 1;
  }

  Shader::Program progSimple(shaderProgram);
  Shader::Program progFragmentLighting(fragmentLightingId);

  // テクスチャを作成する.
  const int tw = 8; // 画像の幅.
  const int th = 8; // 画像の高さ.
  const GLuint B = 0xff'00'00'00; // 黒.
  const GLuint W = 0xff'ff'ff'ff; // 白.
  const GLuint imageData[tw * th] = {
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    W, W, B, W, W, W, W, W,
    B, B, B, B, B, B, B, B,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    W, W, W, W, W, W, B, W,
    B, B, B, B, B, B, B, B,
  };
  GLuint texId = Texture::CreateImage2D(tw, th, imageData, GL_RGBA, GL_UNSIGNED_BYTE);
  GLuint texHouse = Texture::LoadImage2D("Res/House.tga");

  // ライトの設定.
  Shader::LightList lights;
  lights.ambient.color = glm::vec3(0.05f, 0.1f, 0.1f);
  lights.directional.direction = glm::normalize(glm::vec3(5, -2, -2));
  lights.directional.color = glm::vec3(1, 1, 1);
  lights.point.position[0] = glm::vec3(5, 4, 0);
  lights.point.color[0] = glm::vec3(1.0f, 0.8f, 0.4f) * 100.0f;
  lights.spot.position[0] = glm::vec3(-10, 4, 0);
  lights.spot.dirAndCutOff[0] = glm::vec4(glm::normalize(glm::vec3(2, -1, -2)), std::cos(glm::radians(20.0f)));
  lights.spot.color[0] = glm::vec3(0.4f, 0.8f, 1.0f) * 200.0f;

  // メインループ.
  while (!window.ShouldClose()) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 視点を回転移動させる.
    static float degree = 0.0f;
    degree += 0.01f;
    if (degree >= 360.0f) { degree -= 360.0f; }
    const glm::vec3 viewPos = glm::rotate(glm::mat4(1), glm::radians(degree), glm::vec3(0, 1, 0)) * glm::vec4(-20, 30, -30, 1);

    // ポイント・ライトを移動させる.
    if (window.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
      lights.point.position[0].x -= 0.05f;
    } else if (window.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      lights.point.position[0].x += 0.05f;
    }
    if (window.GetKey(GLFW_KEY_UP) == GLFW_PRESS) {
      lights.point.position[0].z -= 0.05f;
    } else if (window.GetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
      lights.point.position[0].z += 0.05f;
    }

    progFragmentLighting.Use();

    // 座標変換行列を作成する.
    const glm::mat4x4 matProj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
    const glm::mat4x4 matView = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    progFragmentLighting.SetViewProjectionMatrix(matProj * matView);

    // 光源を設定する.
    progFragmentLighting.SetLightList(lights);

    progFragmentLighting.BindVertexArray(vao);
    progFragmentLighting.BindTexture(0, texId);

    const float treeCount = 10; // 木を植える本数.
    const float radius = 8; //　半径.
    for (float i = 0; i < treeCount; ++i) {
      const float theta = 3.14f * 2 / treeCount * i;
      const float x = std::cos(theta) * radius;
      const float z = std::sin(theta) * radius;
      progFragmentLighting.Draw(meshList[0], glm::vec3(x, 0, z), glm::vec3(0, theta * 5, 0), glm::vec3(1));
    }

    progFragmentLighting.Draw(meshList[3], glm::vec3(0), glm::vec3(0), glm::vec3(1));

    progSimple.Use();
    progSimple.SetViewProjectionMatrix(matProj * matView);
    progSimple.BindVertexArray(vao);

    progSimple.BindTexture(0, texHouse);
    progSimple.Draw(meshList[1], glm::vec3(0), glm::vec3(0), glm::vec3(1));
    progSimple.BindTexture(0, texId);
    progSimple.Draw(meshList[2], glm::vec3(4, 0, 0), glm::vec3(0), glm::vec3(1));

    // ポイント・ライトの位置が分かるように適当なモデルを表示.
    progSimple.BindTexture(0, texId);
    static float pointLightAngle = 0;
    pointLightAngle += glm::radians(1.0f);
    if (pointLightAngle > glm::radians(360.0f)) {
      pointLightAngle -= glm::radians(360.0f);
    }
    for (int i = 0; i < 8; ++i) {
      progSimple.Draw(meshList[0], lights.point.position[i], glm::vec3(0, pointLightAngle, 0), glm::vec3(1.0f, -0.25f, 1.0f));
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);

    window.SwapBuffers();
  }

  glDeleteTextures(1, &texHouse);
  glDeleteTextures(1, &texId);
  glDeleteVertexArrays(1, &vao);

  return 0;
}
