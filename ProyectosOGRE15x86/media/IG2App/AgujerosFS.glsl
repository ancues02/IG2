#version 330 core

uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform vec4 InColor; 
uniform vec4 OutColor;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader
uniform float Flipping;

void main() {
    bool frontFacing = (Flipping > -1)? gl_FrontFacing : ! gl_FrontFacing; 
    vec3 color = vec3(texture(texturaL, vUv0)); // acceso a téxel

    if (frontFacing) {
        color*=vec3(OutColor.x,OutColor.y,OutColor.z);
    }
    else
        color*=vec3(InColor.x,InColor.y,InColor.z);
   
    fFragColor = vec4(color, 1.0); // out
     if (fFragColor.r >= 0.5)
      discard; 
}