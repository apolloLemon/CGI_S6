#include "init.h"
#include "ppm.h"

/* The number of our GLUT window */
int window; 


// int nombre_returns = 0;
extern GLfloat z;
extern GLfloat xrot;   
extern GLfloat yrot;
GLuint texture[1];
GLuint  blend = 1;
GLuint  light = 0;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLsizei Width, GLsizei Height)	// We call this right after our OpenGL window is created.
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// This Will Clear The Background Color To Black
    //glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    /*    glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do */
    //glDepthFunc(GL_LEQUAL);	  // Le type de test de profondeur 
    //glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				// Reset The Projection Matrix
    
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
    
    glMatrixMode(GL_MODELVIEW);

    // setup blending
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency

    //lumiere();


    /*GLfloat textCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };*/

    TEXTURE_STRUCT * txtstrct = readPpm ("nagoir.ppm");

    GLuint texture[1];
    glGenTextures(1,texture);
    glBindTexture(GL_TEXTURE_2D,texture[0]);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_MIRRORED_REPEAT
    );
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_MIRRORED_REPEAT
    );
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR
    );


    glTexImage2D(GL_TEXTURE_2D,
        0,GL_RGB,
        txtstrct->width,txtstrct->height,
        0,GL_RGB,GL_UNSIGNED_BYTE, 
        txtstrct->data);

    /*glTexEnvf(
        GL_TEXTURE_ENV,
        GL_TEXTURE_ENV_MODE,
        GL_REPLACE
    );*/

    glEnable(GL_TEXTURE_2D);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
    if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
	Height=1;

    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}


/* The function called whenever a normal key is pressed. */
void specialKeyPressed(int key, int x, int y) 
{
    /* avoid thrashing this procedure */
    usleep(100);

    switch (key) {    
    case GLUT_KEY_PAGE_UP: // move the cube into the distance.
	z-=0.02f;
	break;
    
    case GLUT_KEY_PAGE_DOWN: // move the cube closer.
	z+=0.02f;
	break;

    case GLUT_KEY_UP: // decrease x rotation speed;
	xrot-=30.0f;
	break;

    case GLUT_KEY_DOWN: // increase x rotation speed;
	xrot+=30.0f;
	break;

    case GLUT_KEY_LEFT: // decrease y rotation speed;
	yrot-=30.0f;
	break;
    
    case GLUT_KEY_RIGHT: // increase y rotation speed;
	yrot+=30.0f;
	break;

    default:
	break;
    }	
}

int notre_init(int argc, char** argv, void (*DrawGLScene)()) 
{  
    /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
       X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
    glutInit(&argc, argv);  

    /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Depth buffer 
     Alpha blending */  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  

    /* get a 640 x 480 window */
    glutInitWindowSize(640, 480);  

    /* the window starts at the upper left corner of the screen */
    glutInitWindowPosition(0, 0);  

    /* Open a window */  
    window = glutCreateWindow("OpenGL");  

    /* Register the function to do all our OpenGL drawing. */
    glutDisplayFunc(DrawGLScene);  

    /* Go fullscreen.  This is as soon as possible. */
    //    glutFullScreen();

    /* Even if there are no events, redraw our gl scene. */
    glutIdleFunc(DrawGLScene); 

    /* Register the function called when our window is resized. */
    glutReshapeFunc(&ReSizeGLScene);

    /* Register the function called when the keyboard is pressed. */
    glutKeyboardFunc(&touche_pressee);

    /* Register the function called when special keys (arrows, page down, etc) are pressed. */
    glutSpecialFunc(&specialKeyPressed);

    /* Initialize our window. */
    InitGL(640, 480);
  
    /* Start Event Processing Engine */  
    glutMainLoop();  

    return 1;
}

