#version 330
          
uniform sampler2D gSampler;
smooth in vec2 color; 

out vec4 frag_color; 

void main(void) 
{ 
   frag_color = texture2D(gSampler, color.xy); 
} 
