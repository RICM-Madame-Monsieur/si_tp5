// Version d'OpenGL
#version 150

//highp float;
out vec4 frag_color;
in vec2 vert_pos;

// Fonction appellee pour chaque fragment
void main()
{


  vec2 XY = (vert_pos + vec2(1.0)) * 0.5;
    
  frag_color = vec4 (XY, 0.5, 1.0);

}
