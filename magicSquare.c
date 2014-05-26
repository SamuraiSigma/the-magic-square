/*************************************************************************

   >>> Author: Cyrus095

   > Compiling from Terminal:
   $ gcc -lGL -lGLU -lglut magicSquare.c -o magicSquare

   > Special Thanks:
   This code was based off the OpenGL 2.0 tutorials on:
   http://www.swiftless.com/opengltuts.html

*************************************************************************/

#include <stdbool.h> /* true, false, bool */
#include <GL/glut.h> /* For pretty much everything... */

/* Keyboard arrays */
bool keyStates[256]        = {false};
bool keySpecialStates[256] = {false};

/* Variables that control the square's movement */
float horiz = 0.0;
float vert  = 0.0;

/*----------------------------------------------------------------*/

void display();
void reshape(int width, int height);

void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keySpecial(int key, int x, int y);
void keySpecialUp(int key, int x, int y);

void keyOperations();
void keySpecialOperations();

void drawSquare();

/*----------------------------------------------------------------*/
/*--------------------------- MAIN -------------------------------*/
/*----------------------------------------------------------------*/

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE); /* Set up a basic single display buffer */

   glutInitWindowSize(500, 500); /* Width, height */
   glutInitWindowPosition(100, 100);
   glutCreateWindow("The Magic Square (hold Arrow keys for movement)");

   /* ---- Rendering Functions ---- */

   glutDisplayFunc(display);

   glutReshapeFunc(reshape);

   glutKeyboardFunc(keyPressed); /* Use the "keyPressed" function for key presses */
   glutKeyboardUpFunc(keyUp);    /* Use the "keyUp" function for key up events */

   glutSpecialFunc(keySpecial);
   glutSpecialUpFunc(keySpecialUp);

   /* ---- Rendering Functions ---- */

   glutMainLoop(); /* Loops rendering functions */

   return 0;
}

/*----------------------------------------------------------------*/
/*------------------------ FUNCTIONS -----------------------------*/
/*----------------------------------------------------------------*
      display ()

      Draws in the OpenGL window.
*/

void display()
{
   /* Handle keys */
   keyOperations();
   keySpecialOperations();

   glClearColor(0.0f, 0.0f, 0.0f, 1.f); /* Clear the background of our window to a fixed color */
   glClear(GL_COLOR_BUFFER_BIT);        /* Clear the colour buffer (more buffers later on) */
   glLoadIdentity();                    /* Load the Identity Matrix to reset our drawing locations */
   glTranslatef(0.0f, 0.0f, -5.0f);     /* Push eveything 5 units back into the scene (because near plane is at z = 1.0) */
   drawSquare();
   glFlush();                           /* Flush the OpenGL buffers to the window */
}

/*----------------------------------------------------------------*
      reshape (width, height)

      Uses the current OpenGL window's width and height.
      Resizes the OpenGL window's size and its components.
*/

void reshape(int width, int height)
{ 
   glViewport(0, 0, (GLsizei)width, (GLsizei)height); /* From (0,0) to (width, height) */
   glMatrixMode(GL_PROJECTION); /* Switch to the projection matrix so that we can manipulate
                                   how our scene is viewed */
   glLoadIdentity(); /* Reset the projection matrix to the identity matrix so that we don't
                        get any artifacts (cleaning up) */
   gluPerspective(60, (GLfloat) width / (GLfloat) height, 1.0, 100.0); /* Set the FOV angle (in degrees), the aspect ratio
                                                                          of our window, and the near and far planes */
   glMatrixMode(GL_MODELVIEW);
} 

/*----------------------------------------------------------------*
      keyPressed (key, x, y)

      Recieves a currently pressed keyboard key, along with the
      location of the mouse when the key was pressed.
*/

void keyPressed(unsigned char key, int x, int y)
{
   keyStates[key] = true;
}

/*----------------------------------------------------------------*
      keyUp (key, x, y)

      Recieves a currently released keyboard key, along with the
      location of the mouse when the key was released.
*/

void keyUp(unsigned char key, int x, int y)
{  
   keyStates[key] = false;
}


/*----------------------------------------------------------------*
      keySpecial (key, x, y)

      Recieves a currently pressed special key, along with the
      location of the mouse when the key was pressed.
*/

void keySpecial(int key, int x, int y)
{
   keySpecialStates[key] = true;
}

/*----------------------------------------------------------------*
      keySpecialUp (key, x, y)

      Recieves a currently released special key, along with the
      location of the mouse when the key was released.
*/

void keySpecialUp(int key, int x, int y)
{
   keySpecialStates[key] = false;
}

/*----------------------------------------------------------------*
      keyOperations ()

      Does something depending on whether a key is pressed or not.
*/

void keyOperations()
{
   if (keyStates['q'] || keyStates['Q']) exit(0);

   glutPostRedisplay(); /* For some reason, display() is idle until
                           something must be drawn. This function fixes that */
}

/*----------------------------------------------------------------*
      keySpecialOperations ()

      Does something depending on whether a specialkey is pressed
      or not.
*/

void keySpecialOperations()
{
   if (keySpecialStates[GLUT_KEY_LEFT])  horiz -= 0.001;
   if (keySpecialStates[GLUT_KEY_RIGHT]) horiz += 0.001;
   if (keySpecialStates[GLUT_KEY_DOWN])  vert  -= 0.001;
   if (keySpecialStates[GLUT_KEY_UP])    vert  += 0.001;

   glutPostRedisplay(); /* For some reason, display() is idle until
                           something must be drawn. This function fixes that */
}

/*----------------------------------------------------------------*
      drawSquare ()

      Draws a square. :D
*/

void drawSquare() {

#define V1 -1.0f
#define V2  1.0f

glBegin(GL_QUADS); /* Start drawing a quad */ 
   glColor3f(1.0f, 0.0f, 0.0f);
   glVertex3f(V1 + horiz, V1 + vert, 0.0f); /* bottom left  */

   glColor3f(0.0f, 1.0f, 0.0f);
   glVertex3f(V1 + horiz, V2 + vert, 0.0f);  /* top left     */

   glColor3f(0.0f, 0.0f, 1.0f);
   glVertex3f(V2 + horiz, V2 + vert, 0.0f);   /* top right    */

   glColor3f(1.0f, 1.0f, 0.0f);
   glVertex3f(V2 + horiz, V1 + vert, 0.0f);  /* bottom right */
glEnd(); /* Finished drawing! */

}
