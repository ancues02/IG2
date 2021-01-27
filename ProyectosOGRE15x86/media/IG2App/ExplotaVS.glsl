#version 330 core
in vec4 vertex;
in vec3 normal;
in vec2 uv0;

out vec2 vUv0;
out vec3 vNormal_;


//TODOESTO EN LOCALES PARA EL GS
void main(){
    vNormal_ = normalize( normal);
    vUv0=uv0;
    gl_Position = vertex;
}