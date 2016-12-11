#version 330

smooth in vec3 fN;
smooth in vec3 fL;
smooth in vec3 fE;
smooth in vec2 _texture;

smooth in vec3 worldPos;
smooth in vec3 worldNormal;

out vec4 frag_color;

uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform float Shininess = .1;
uniform sampler2D gSampler;

uniform vec4 lightPosition = vec4( -30.0, 20.0, 0.0, 0.0 );
uniform vec3 eyePosition;

void main() 
{   
  vec3 N = normalize(fN);
  vec3 E = normalize(fE);
  vec3 L = normalize( vec3( lightPosition ) - worldPos);
  vec3 V = normalize( eyePosition - worldPos );

  vec3 H = normalize( L + E );   
  vec4 ambient = AmbientProduct;

  float LdotN = max(0.0, dot(L, worldNormal));

  float Kd = max(dot(L, worldNormal), 0.0);
  vec4 diffuse = LdotN * DiffuseProduct;
    

  vec3 R = -normalize(reflect(L, worldNormal));
  float Ks = pow(max(dot(L, H), 0.0), Shininess);
  vec4 specular = SpecularProduct * Ks;



  if( dot(L, N) < 0.0 ) 
  specular = vec4(0.0, 0.0, 0.0, 1.0);
  
  frag_color = texture2D( gSampler, _texture.xy ) + ambient + diffuse + specular;
  frag_color.a = 1.0;
} 
