#version 330 core // archivo LuminancePS.glsl
in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
uniform float kernel[9];
out vec4 fFragColor;




void main() {
    ivec2 texSize =textureSize(RTT0,0);
    float incS = 1/float(texSize.s);//desplazamiento
    float incT=1/float(texSize.t);
    
    vec2 incUV[9];//texels vecinos
    incUV[0] = vec2(-incS,incT);
    incUV[1] = vec2(-incS,incT);
    incUV[2] = vec2(-incS, -incT);
    incUV[3] = vec2(0.0, incT);
    incUV[4] = vec2(0.0,0.0);
    incUV[5] = vec2(0.0, -incT);
    incUV[6] = vec2(incS, incT);
    incUV[7] = vec2(incS, 0.0);
    incUV[8] = vec2(incS, -incT);  

    vec3 color= vec3(0.0);

    
    for(int i = 0; i < 9; i++){//cogemos los colores de los texels vecinos
        vec3 tmp = texture(RTT0, vUv0+incUV[i]).rgb;
        color+=tmp*kernel[i];
    }
    
    fFragColor = vec4(color, 1.0);
}