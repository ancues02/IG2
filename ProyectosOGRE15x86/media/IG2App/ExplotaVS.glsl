#version 330 core
in vec4 vertex;
in vec2 uV0;
in vec3 normal;
out vec2 vUv0;
out vec3 vViewNormal_;
out vec3 vViewVertex_;

uniform mat4 modelViewMat; 
uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 normalMat;


void main(){
    vUv0=uV0;
    vViewVertex_=vec3(modelViewMat * vertex);
    vViewNormal_ = normalize(vec3(normalMat * vec4(normal,0)));
    gl_Position = vertex;
}