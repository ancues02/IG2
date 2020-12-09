#version 330 core

uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform vec4 InColor; 
uniform vec4 OutColor;
in vec3 vFrontColor; // color de la iluminación interpolado
in vec3 vBackColor; // color de la iluminación interpolado
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader
uniform float Flipping;

void main() {
    bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing; 
    vec3 color = texture(texturaL, vUv0).rgb;
    if (color.r >= 0.5)
      discard;
    if (frontFacing) color = vFrontColor  * OutColor.rgb;
    else color = vBackColor  * InColor.rgb;
    fFragColor = vec4(color, 1.0);
    
}