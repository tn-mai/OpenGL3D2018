/**
* @file FragmentLighting.frag
*/
#version 410

layout(location=0) in vec3 inPosition;
layout(location=1) in vec4 inColor;
layout(location=2) in vec2 inTexCoord;
layout(location=3) in vec3 inNormal;

out vec4 fragColor;

// 環境光.
struct AmbientLight
{
  vec3 color;
};

// 指向性ライト.
struct DirectionalLight
{
  vec3 direction;
  vec3 color;
};

// ポイントライト.
struct PointLight
{
  vec3 position[8];
  vec3 color[8];
};

// スポットライト
struct SpotLight
{
  vec3 position[4];
  vec4 dirAndCutOff[4];
  vec3 color[4];
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform sampler2D texColor;

/**
* フラグメントシェーダー.
*/
void main()
{
  // 指向性ライトの明るさを計算する.
  float cosTheta = clamp(dot(inNormal, -directionalLight.direction), 0, 1);
  vec3 lightColor = directionalLight.color * cosTheta;

  // ポイントライトの明るさを計算する.
  for (int i = 0; i < 8; ++i) {
    if (dot(pointLight.color[i], pointLight.color[i]) != 0) {
      vec3 lightVector = (pointLight.position[i] - inPosition);
      float power = 1 / dot(lightVector, lightVector);
      float cosTheta = clamp(dot(inNormal, normalize(lightVector)), 0, 1);
      lightColor += pointLight.color[i] * cosTheta * power;
	}
  }

  // スポットライトの明るさを計算する.
  for (int i = 0; i < 4; ++i) {
    if (dot(spotLight.color[i], spotLight.color[i]) != 0) {
      vec3 lightLine = (spotLight.position[i] - inPosition);
	  vec3 lightVector = normalize(lightLine);
	  float cutOff = smoothstep(spotLight.dirAndCutOff[i].w, 1, dot(-lightVector, spotLight.dirAndCutOff[i].xyz));
      float power = 1 / dot(lightLine, lightLine) * cutOff;
      float cosTheta = clamp(dot(inNormal, lightVector), 0, 1);
      lightColor += spotLight.color[i] * cosTheta * power;
	}
  }

  fragColor = inColor * texture(texColor, inTexCoord);
  fragColor.rgb = (fragColor.rgb * lightColor);
  fragColor.rgb += ambientLight.color;
}
