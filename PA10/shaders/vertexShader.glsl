#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
in vec3 vColor;
in vec3 vNormal;


out vec4 color;
smooth out vec2 texture;

uniform mat4 Projection, Model, View;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;

void main(void)
{

  vec4 v = vec4( vPosition, 1.0 );

  vec3 pos = (Model * View * v).xyz;

  vec3 L = normalize( LightPosition.xyz - pos );
  vec3 E = normalize( -pos );
  vec3 H = normalize( L + E );

  vec3 N = normalize( Model * View * vec4( vNormal, 0.0 )).xyz;

  vec4 ambient = AmbientProduct;

  float Kd = max( dot(L, N), 0.0 );
  vec4  diffuse = Kd*DiffuseProduct;
  float Ks = pow( max(dot(N, H), 0.0), Shininess );
  vec4  specular = Ks * SpecularProduct;
  if( dot(L, N) < 0.0 )  specular = vec4(0.0, 0.0, 0.0, 1.0); 
  gl_Position = Projection * View * Model * v;

  texture = vTexture;

  color = vec4( vColor.rgb, 1.0 );

  color = ambient + diffuse + specular;
  color.a = 1.0;
}
