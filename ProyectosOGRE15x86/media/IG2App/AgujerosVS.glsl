#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0

uniform mat4 modelViewMat; 
uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 normalMat;

uniform vec3 lightAmbient; 
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

uniform vec3 materialDiffuse;
// out vec4 gl_Position; // obligatoria predefinida
out vec2 vUv0; // out del vertex shader
out vec3 vFrontColor;
out vec3 vBackColor;
 
float  diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir=lightPosition.xyz;
    if(lightPosition.w==1)
        lightDir=lightPosition.xyz-cVertex;
    return max(dot(cNormal,normalize(lightDir)),0.0);
}

void main(){
    vec3 ambient = lightAmbient * materialDiffuse; 
	vec3 viewVertex = vec3(modelViewMat * vertex);
	vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;

	vFrontColor = ambient + diffuse;
    diffuse=diff(viewVertex,-viewNormal)*lightDiffuse* materialDiffuse;
    vBackColor=ambient + diffuse;
    vUv0=uv0;
    gl_Position=modelViewProjMat * vertex;
}