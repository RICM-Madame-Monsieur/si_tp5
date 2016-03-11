#include <iostream>
#include <vector>
#include <string>

#include <shader.h> // Help to load shaders from files

// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h>    // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/ 
#include <GL/glfw.h>    // Window, keyboard, mouse : http://www.glfw.org/

#include <glm/glm.hpp>  // OpenGL Mathematics : http://glm.g-truc.net/0.9.5/index.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <GLFW_define.h>
#include <Mesh.h>

// Dimensions de la fenêtre :
#define WIDTH 1000.0f
#define HEIGHT 800.0f

using namespace glm;
using namespace std;


void view_control(vec2& bl, vec2& tr, float dx);

int main()
{

    cout << "Debut du programme..." << endl;

    //==================================================
    //============= Creation de la fenetre =============
    //==================================================


    // Initialisation de GLFW
	if( !glfwInit() )
	{
		cout << "Echec de l'initialisation de GLFW" << endl;
		exit(EXIT_FAILURE);
	}

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 2.1
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);


    GLFWvidmode return_struct;
    glfwGetDesktopMode( &return_struct );
    int height = return_struct.Height;
    int width = return_struct.Width;

    // Ouverture d'une fenêtre en 1024x768
    // et creation d'un contexte OpenGL
//    auto window = glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW )
//    if( window == NULL )
//    if(!glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW ))
//    if(!glfwOpenWindow(WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_FULLSCREEN))
    if(!glfwOpenWindow(width, height, 0,0,0,0, 32,0, GLFW_FULLSCREEN))
	{
		cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
    }

    // Definition du titre de la fenêtre
	glfwSetWindowTitle( "Polytech RICM 4 - TP5" );

    // Autorise GLFW a recevoir les appuis de touche
	glfwEnable( GLFW_STICKY_KEYS );

    // Initialisation de  GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Echec de l'initialisation de GLEW" << endl;
		exit(EXIT_FAILURE);
	}
    
    // Verification des donnees du contexte OpenGL
    const GLubyte* renderer = glGetString (GL_RENDERER);
    cout << "Carte Graphique : " << renderer << endl;

    const GLubyte* version = glGetString (GL_VERSION);
    cout << "Driver OpenGL : " << version << endl;


    //==================================================
    //================= Initialisation =================
    //==================================================

    cout << "Initialisations..." << endl;


    // Definition de la couleur du fond
    glClearColor(0.1, 0.1, 0.1, 0.0);



//-------------------------------------------------
// Initialisation du shader programm

    // Compilation du shader programm
	GLuint programID = LoadShaders( "../shader/vertex.glsl", "../shader/fragment.glsl" );
    cout << "programID = " << programID << endl;




//-------------------------------------------------
// Initialisation des arrays de données

    unsigned int index[] = {0, 1, 3, 0, 3, 2};

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    cout << "elementbuffer = " << elementbuffer << endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
    

    cout << "Debut de la boucle principale..." << endl;

    float init_time = glfwGetTime();
    float prec_time = init_time;
    float cur_time = init_time;
    
    float speed = 0.5;
    

    // Boucle de dessin
	do{
        // Nettoyage de la zone de dessin
		glClear( GL_COLOR_BUFFER_BIT );
		glClear( GL_DEPTH_BUFFER_BIT );


        prec_time = cur_time;
        cur_time = glfwGetTime() - init_time;
        double delta_time = cur_time - prec_time;

        glfwSetWindowTitle( (string("Polytech RICM 4 - TP5 - ") + detail::format("%2.0f", 1.0/ delta_time) + string(" FPS")).c_str() );


        //==================================================
        //===================== Dessin =====================
        //==================================================

		// Definition de programID comme le shader courant
		glUseProgram(programID);



        // Index buffer
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        


         // Draw the triangles !
         glDrawElements(
             GL_TRIANGLES,      // mode
             6,                 // nombre
             GL_UNSIGNED_INT,   // type
             (void*)0           // offset
         );



		// Echange des zones de dessin buffers
		glfwSwapBuffers();

        cout << "Temps ecoule : " << cur_time << "\ts\r";
        cout.flush();

    } // Execution de la boucle...
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
           glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

    cout << endl;

    // Ferme GLFW et OpenGL
	glfwTerminate();



    //==================================================
    //============== Nettoyage la memoire ==============
    //==================================================

    // Liberation des buffers
    glDeleteBuffers(1, &elementbuffer);



    cout << "Fin du programme..." << endl;


	return EXIT_SUCCESS;
}

