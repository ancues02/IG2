#version 330 core 
layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;
uniform float tiempo2pi;
uniform mat4 modelViewProjMat;

const float VD=50;
in vec2 _gTexCoor[];
 //in vec2 vUv0;
 out vec2 _vUv0;
//in vec3 vViewNormal;
//in vec3 vViewVertex;

//out vec3 vViewNormal;
//out vec3 vViewVertex;

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
   
   

    vec3 vertices[3] = vec3[](  gl_in[0].gl_Position.xyz, 
                                gl_in[1].gl_Position.xyz,
                                gl_in[2].gl_Position.xyz);

    vec3 dir = baricentroVec(vertices);
    for(int i = 0; i < 3; ++i){
        vec3 posDes = vertices[i] + dir * VD;
         _vUv0=_gTexCoor[i];
            //vUv1= (uv0 - 0.5) * (SinTiempo*0.25 + 0.75) + 0.5;  
        //gl_Position.x=gl_Position.x*cos(tiempo2pi)+sin(tiempo2pi)*gl_Position.z;
        //gl_Position.z=gl_Position.x*-sin(tiempo2pi)+cos(tiempo2pi)*gl_Position.z;
        gl_Position = modelViewProjMat * vec4(posDes, 1.0);
       
        EmitVertex();
    }

    EndPrimitive();
    
}