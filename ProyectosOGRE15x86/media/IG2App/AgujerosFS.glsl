#version 330 core

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy; // tipo sampler2D para texturas 2D
uniform vec4 InColor; 
uniform vec4 OutColor;
in vec3 vViewNormal;
in vec3 vViewVertex;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader
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
    vec3 color = texture(texturaCorrosion, vUv0).rgb;
    if (color.r >= 0.65)
      discard;
      
    vec3 diffuse;
    vec3 vColor;
    if(frontFacing){//ponemos textura a la cara front y le aplicamos su color y sus luces
        diffuse= diff(vViewVertex, vViewNormal) * lightDiffuse * materialDiffuse;
        vColor = ambient + diffuse;
        color = vColor * texture(texturaBumpy, vUv0).rgb * OutColor.rgb;
    }
    else{//aplicamos color y luces a la cara back, no le ponemos textura
        diffuse=diff(vViewVertex,-vViewNormal)*lightDiffuse* materialDiffuse;
        vColor = ambient + diffuse;
        color = vColor  * InColor.rgb;
    }    
    fFragColor = vec4(color, 1.0);
    
}