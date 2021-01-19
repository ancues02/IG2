#version 330 core 
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;
uniform float tiempo2pi;
uniform mat4 modelViewProjMat;
uniform float tiempo;

const float VD=50;
const float scale = 2;
in vec2 vUv0[];
 //in vec2 vUv0;
 out vec2 _vUv0;
in vec3 vViewNormal_[];
in vec3 vViewVertex_[];

out vec3 vViewNormal;
out vec3 vViewVertex;

vec3 normalVec(vec3 v[3]){
    vec3 normal= normalize(cross ((v[2]-v[1]),(v[0]-v[1])));
    return normal;
}//vector normal al triangulo

vec3 baricentroVec(vec3 v[3]){
    vec3 baricentro=vec3((v[0].x+v[1].x+v[2].x)/3,
    (v[1].y+v[2].y+v[0].y)/3,
    (v[1].z+v[2].z+v[0].z)/3);
    return normalize(baricentro);
}//pos baricentro del triangulo

void main(){
   
    mat4 yawMatrix = mat4(
       vec4(cos(tiempo2pi), 0.0, sin(tiempo2pi), 0.0),
       vec4(           0.0, 1.0,            0.0, 0.0),
       vec4(-sin(tiempo2pi), 0.0, cos(tiempo2pi), 0.0),
       vec4(            0.0, 0.0,           0.0, 1.0)
   );

    vec3 vertices[3] = vec3[](  gl_in[0].gl_Position.xyz * tiempo, 
                                gl_in[1].gl_Position.xyz * tiempo,
                                gl_in[2].gl_Position.xyz * tiempo);

    vec3 dir = baricentroVec(vertices);
    for(int i = 0; i < 3; ++i){
        vec3 posDes = vertices[i] + dir * VD * tiempo;
        _vUv0=vUv0[i];
        
        mat4 aux = (modelViewProjMat * yawMatrix);
        vViewNormal=vViewNormal_[i];
        vViewVertex=vViewVertex_[i];
        gl_Position = aux * vec4(posDes, 1.0);
        
        EmitVertex();
    }

    EndPrimitive();
    
}