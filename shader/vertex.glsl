// Version d'OpenGL
#version 150

out vec2 vert_pos;

void main()
{
    vert_pos = vec2(0.0);
    switch(gl_VertexID)
    {
    case 0:
        //Bottom-left
        vert_pos = vec2(-1.0, -1.0);
        break;
    case 1:
        //Top-left
        vert_pos = vec2(-1.0, 1.0);
        break;
    case 2:
        //Bottom-right
        vert_pos = vec2(1.0, -1.0);
        break;
    case 3:
        //Top-right
        vert_pos = vec2(1.0, 1.0);
        break;
    }
    
    gl_Position = vec4(vert_pos, 0.0, 1.0);
}
