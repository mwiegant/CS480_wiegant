
#version 330

layout (location = 0) in vec4 v_position;
layout (location = 1) in vec2 v_texture;

in vec4 normal;

smooth out vec2 _texture;
smooth out vec3 R;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

void main(void)
{
  gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v_position;
  vec3 N = normalize(normalMatrix * normal);
  vec4 eyePos = (modelMatrix * viewMatrix * gvPosition);
  R = reflect(-eyePos.xyz, N);
  _texture = v_texture;
}
