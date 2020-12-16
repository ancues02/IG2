#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
// out vec4 gl_Position; // obligatoria predefinida
out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // out del vertex shader
//uniform float ZF;
uniform float SinTiempo;
 
void main() {
    vUv0 = uv0; // se pasan las coordenadas de textura
    //    vUv1= (uv0-0.5) * ZF + 0.5;
    vUv1= (uv0 - 0.5) * (SinTiempo*0.25 + 0.75) + 0.5;  
    gl_Position = modelViewProjMat * vertex; //obligatorio
}