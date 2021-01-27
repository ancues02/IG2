#version 330 core // archivo ExplotaFS.glsl
out vec4 fFragColor;
uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy; // tipo sampler2D para texturas 2D

in vec3 vNormal;
in vec3 vVertex;
in vec2 _vUv0;
uniform float Flipping;

uniform vec3 lightAmbient; 
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

uniform vec3 materialDiffuse;

float  diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir=lightPosition.xyz;
    if(lightPosition.w==1)
        lightDir=lightPosition.xyz-cVertex;
    return max(dot(cNormal,normalize(lightDir)),0.0);
}

void main() {

    bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing; 

    vec3 ambient = lightAmbient * materialDiffuse; 
    vec3 color;
 
    vec3 diffuse;
    vec3 vColor;
    if(frontFacing){
        diffuse= diff(vVertex, vNormal) * lightDiffuse * materialDiffuse;
        vColor = ambient + diffuse;
        color = vColor * texture(texturaBumpy, _vUv0).rgb ;
    }
    else{
        diffuse=diff(vVertex,-vNormal)*lightDiffuse* materialDiffuse;
        vColor = ambient + diffuse;
        color = vColor  * texture(texturaCorrosion, _vUv0).rgb;
    }    


    fFragColor =vec4(color, 1.0);
}