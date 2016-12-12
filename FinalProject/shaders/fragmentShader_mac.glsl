#version 330

smooth in vec3 fragNormal;
smooth in vec3 fragVert;
smooth in vec2 fragTexture;

out vec4 frag_color;

uniform vec3 lightPosition = vec3( -30.0, 20.0, 0.0 );
uniform sampler2D gSampler;

uniform mat4 Model;

void main()
{
    mat3 normalMat = transpose( inverse ( mat3( Model ) ) );
    vec3 normal = normalize( normalMat * fragNormal );

    vec3 fragPos = vec3( Model * vec4( fragVert, 1 ) );

    vec3 surfaceToLight = lightPosition - fragPos;

    float brightness = dot( normal, surfaceToLight ) / ( length( surfaceToLight ) * length( normal));
    brightness = clamp( brightness, 0, 1 );

    vec4 surfaceColor = texture( gSampler, fragTexture );
    frag_color = vec4( brightness * vec3(1, 1, 1) * surfaceColor.rgb, surfaceColor.a );
}