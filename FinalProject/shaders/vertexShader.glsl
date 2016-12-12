#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;

smooth out vec3 fragNormal;
smooth out vec3 fragVert;
smooth out vec2 fragTexture;

uniform vec3 eyePosition;

uniform mat4 Model, View, Projection;

void main() 
{
  vec4 eyeDeal = vec4( eyePosition, 1 );

  fragTexture = vTexture;
  fragVert = vPosition;
  fragNormal = vNormal;

  gl_Position = Projection * View * Model * vec4(vPosition, 1);
}
