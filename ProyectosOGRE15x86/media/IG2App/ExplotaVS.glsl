#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

out vec2 vUv0;
out vec3 vViewNormal_;
out vec3 vViewVertex_;

uniform mat4 modelViewMat; 
uniform mat4 normalMat;


void main(){
    vViewVertex_=vec3(modelViewMat * vertex);
    vViewNormal_ = normalize(vec3(normalMat * vec4(normal,0)));
    vUv0=uv0;
    gl_Position = vertex;
}