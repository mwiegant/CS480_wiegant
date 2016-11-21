#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;

smooth out vec3 fN;
smooth out vec3 fE;
smooth out vec3 fL;
smooth out vec2 _texture;

uniform mat4 Model, View, Projection;
uniform vec4 LightPosition = vec4( 0.0, 3.0, 3.0, 3.0 );

void main()
{
  fN = vNormal;
  fE = vPosition.xyz;
  fL = LightPosition.xyz;
    
  if( LightPosition.w != 0.0 ) 
  {
	 fL = LightPosition.xyz - vPosition.xyz;
  }

  gl_Position = Projection * View * Model * vPosition;

  _texture = vTexture;
}
