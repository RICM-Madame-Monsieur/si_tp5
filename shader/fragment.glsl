// Version d'OpenGL
#version 150

//highp float;
out vec4 frag_color;
in vec2 vert_pos;

uniform float p0;
uniform float p1;
uniform float zoom;
uniform float t;

#define S 1000
#define N 1000

// fonction calculant le carre d'un nombre complexe²
vec2 carreComplexe(vec2 nombreComplexe){
    float a = nombreComplexe.x;
    float b = nombreComplexe.y;
    return vec2 ((a*a - b*b), 2*a*b);
}

// fonction qui calcule la couleur à partir d'un nombre entier
vec3 colorMap(in int n){
    float n_float = float(n);
    float N_float = float(N);
    float s = 1.0;
    float v = 1.0;
    float h = (mod((n_float+(t/100)),N_float)/N_float)*360;

    //return vec3(h);
    
    vec3 hsv = vec3(h, s, v);

    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(hsv.xxx + K.xyz) * 6.0 - K.www);
    return hsv.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hsv.y);
}


// Fonction appellee pour chaque fragment
void main()
{
    
    // p(0,0) = p0
    // p(10,10) = p1 
    
    vec2 z = vec2(0.0, 0.0);
    vec2 z1;
    vec2 z2;
    vec2 z3;
    vec2 z4;
    //vec2 z = vert_pos;
    int n;
        
    for(n=0; n<N; n++){
        z1 = vec2(vert_pos.x      , vert_pos.y      );
        z2 = vec2(vert_pos.x + 1/2, vert_pos.y      );
        z3 = vec2(vert_pos.x      , vert_pos.y + 1/2);
        z4 = vec2(vert_pos.x + 1/2, vert_pos.y + 1/2);
        z = carreComplexe(z) + zoom*(z1+z2+z3+z4)/4.0 + vec2(p0, p1);
        if(sqrt(z.x*z.x + z.y*z.y) > S){
            break;
        }
    }
    

    frag_color = vec4 (colorMap(n),1.0);

    // vec2 XY = (vert_pos + vec2(1.0)) * 0.5;
    // frag_color = vec4 (XY, 0.5, 1.0);

}
