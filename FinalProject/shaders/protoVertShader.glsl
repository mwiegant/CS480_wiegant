#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;

smooth out vec3 fN;
smooth out vec3 fE;
smooth out vec3 fL;
smooth out vec2 _texture;

smooth out vec3 worldPos;
smooth out vec3 worldNormal;

uniform mat4 Model, View, Projection;
uniform vec4 lightPosition = vec4( -30.0, 20.0, 0.0, 0.0 );

void main()
{
  vec3 worldPos = ( mat3( Model ) * vPosition );
  vec3 worldNormal = normalize( mat3( Model ) * vNormal );

  fN = vNormal;
  fE = vPosition.xyz;
  fL = lightPosition.xyz;

  if( lightPosition.w != 0.0 ) 
  {
	 fL = lightPosition.xyz - vPosition.xyz;
  }

  gl_Position = Projection * View * Model * vec4( vPosition, 1 );

  _texture = vTexture;
}
