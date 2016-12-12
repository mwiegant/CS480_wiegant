#version 330

smooth in vec3 fragNormal;
smooth in vec3 fragVert;
smooth in vec2 fragTexture;

out vec4 frag_color;

uniform vec3 eyePosition;

uniform vec3 lightPosition = vec3( 0.0, 20.0, 0.0 );
uniform sampler2D gSampler;

uniform mat4 Model;

void main() 
{   
  vec3 normal = normalize( transpose( inverse ( mat3( Model ) ) ) * fragNormal );
  vec3 surfacePos = vec3( Model * vec4( fragVert, 1 ) );
  vec4 surfaceColor = texture( gSampler, fragTexture );
  vec3 surfaceToLight = normalize( lightPosition - surfacePos );
  vec3 surfaceToCamera = normalize( eyePosition - surfacePos );

  float diffuseCoefficient = max( 0.0, dot(normal, surfaceToLight ) );
  vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * vec3(1, 1, 1);

  vec3 ambient = vec3( .1, .1, .1 );

  float specularCoefficient = 0.0;
  if( diffuseCoefficient > 0.0 )
  {
    specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), float(.1));
  }
  vec3 specular = specularCoefficient * vec3(.1, .1, .1) * vec3(.5, .5, .5);

  vec3 linearColor = ambient + specular + diffuse;

  frag_color = vec4( linearColor, 1 );
} 
