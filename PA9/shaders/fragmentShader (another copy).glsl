#version 330
          
smooth in vec2 _texture;
smooth in vec3 R;

out vec4 frag_color;

uniform sampler2D gSampler;
uniform samplerCube texMap;

void main(void)
{
   frag_color = texture2D(gSampler, _texture.xy);
   gl_FragColor = textureCube(texMap, R);
} 
