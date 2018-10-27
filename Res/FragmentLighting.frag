/**
* @file FragmentLighting.frag
*/
#version 410

layout(location=0) in vec3 inPosition;
layout(location=1) in vec4 inColor;
layout(location=2) in vec2 inTexCoord;
layout(location=3) in vec3 inNormal;

out vec4 fragColor;

// ����.
struct AmbientLight
{
  vec3 color;
};

// �w�������C�g.
struct DirectionalLight
{
  vec3 direction;
  vec3 color;
};

// �|�C���g���C�g.
struct PointLight
{
  vec3 position[8];
  vec3 color[8];
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

uniform sampler2D texColor;

/**
* �t���O�����g�V�F�[�_�[.
*/
void main()
{
  // �w�������C�g�̖��邳���v�Z����.
  float cosTheta = clamp(dot(inNormal, -directionalLight.direction), 0, 1);
  vec3 lightColor = directionalLight.color * cosTheta;

  // �|�C���g���C�g�̖��邳���v�Z����.
  for (int i = 0; i < 8; ++i) {
    if (dot(pointLight.color[i], pointLight.color[i]) != 0) {
      vec3 lightVector = (pointLight.position[i] - inPosition);
      float power = 1 / dot(lightVector, lightVector);
      float cosTheta = clamp(dot(inNormal, normalize(lightVector)), 0, 1);
      lightColor += pointLight.color[i] * cosTheta * power;
	}
  }

  fragColor = inColor * texture(texColor, inTexCoord);
  fragColor.rgb = (fragColor.rgb * lightColor);
  fragColor.rgb += ambientLight.color;
}
