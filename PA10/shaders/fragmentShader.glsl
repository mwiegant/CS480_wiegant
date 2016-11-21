#version 330

smooth in vec3 fN;
smooth in vec3 fL;
smooth in vec3 fE;
smooth in vec2 texture;

out vec4 frag_color;

uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform vec4 LightPosition;
uniform float Shininess;
uniform sampler2D gSampler;

void main() 
{   
  vec3 N = normalize(fN);
  vec3 E = normalize(fE);
  vec3 L = normalize(fL);

  vec3 H = normalize( L + E );   
  vec4 ambient = AmbientProduct;

  float Kd = max(dot(L, N), 0.0);
  vec4 diffuse = Kd*DiffuseProduct;
    
  float Ks = pow(max(dot(N, H), 0.0), Shininess);
  vec4 specular = Ks*SpecularProduct;

  if( dot(L, N) < 0.0 ) 
  specular = vec4(0.0, 0.0, 0.0, 1.0);
  
  frag_color = texture2D( gSampler, texture.xy ) + ambient + diffuse;
  frag_color.a = 1.0;
} 
