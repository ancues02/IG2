#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0

uniform mat4 modelViewMat; 
uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 normalMat;


// out vec4 gl_Position; // obligatoria predefinida
out vec2 vUv0; // out del vertex shader
out vec3 vViewNormal;
out vec3 vViewVertex;
 

void main(){
   
    vViewVertex=vec3(modelViewMat * vertex);
    vViewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    vUv0=uv0;
    gl_Position=modelViewProjMat * vertex;
}