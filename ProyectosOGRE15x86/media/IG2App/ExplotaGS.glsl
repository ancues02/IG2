#version 330 core 
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;
uniform mat4 modelViewProjMat;

uniform mat4 modelViewMat;
uniform mat4 normalMat;

const float VD=50;
in vec2 vUv0[];
//uniform float tiempo2pi;
uniform float tiempo;
 //in vec2 vUv0;
 out vec2 _vUv0;
in vec3 vNormal_[];
//in vec3 vViewVertex_[];

out vec3 vNormal;
out vec3 vVertex;
vec3 normalVec(vec3 v[3]){
    vec3 normal= normalize(cross ((v[2]-v[1]),(v[0]-v[1])));
    return normal;
}//vector normal al triangulo

void main(){
   

    vec3 vertices[3] = vec3[](  gl_in[0].gl_Position.xyz, 
                                gl_in[1].gl_Position.xyz,
                                gl_in[2].gl_Position.xyz);

    vec3 dir = normalVec(vertices);
    for(int i = 0; i < 3; ++i){
        vec3 posDes = vertices[i] + dir * VD * tiempo;
         _vUv0=vUv0[i];
         vNormal=vec3(normalMat * vec4(vNormal_[i],1.0));
         vVertex=vec3(modelViewMat * vec4(posDes,1.0));

        gl_Position = modelViewProjMat * vec4(posDes, 1.0);
        EmitVertex();
    }

    EndPrimitive();
    
}