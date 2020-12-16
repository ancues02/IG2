#version 330 core // archivo LuminancePS.glsl
in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
uniform float kernel[9];
out vec4 fFragColor;




void main() {

    ivec2 texSize = textureSize(RTT0, 0);
    float incS = 1. / float(texSize.s);
    float incT = 1. / float(texSize.t);

    vec3 color = texture(RTT0, vUv0).rgb;
    for(int i = 0; i < 9; i++){
        color += kernel[i] / 16;
    }
    //vec4 sceneColor = texture(RTT0, vUv0);
    //float lum = dot(vec3(sceneColor), WsRGB);
    fFragColor = vec4(color, 1.0);
}