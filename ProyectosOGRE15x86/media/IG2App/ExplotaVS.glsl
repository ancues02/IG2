#version 330 core
in vec4 vertex;
in vec2 uV0;
out vec2 vUv0;
// out vec3 vViewNormal;
// out vec3 vViewVertex;

void main(){
    vUv0=uV0;
    //ViewVertex=vec3(modelViewMat * vertex);
    //vViewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    gl_Position = vertex;
}