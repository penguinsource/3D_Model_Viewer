////////////////////////////////////////////////////          
// Modelviewer for .OBJ files
// Mihai Oprescu
// run compile with 'make'
// run program with './modelviewer [filename].OBJ'
//

#include "Model.h"
#include "Camera.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// initiate a Model object and a display list
GLuint model_list;		// display list
Model model_object;		// an instance of Model
Camera camera_object;	// an instance of Camera

// global variables
static int isWire = 1; // wireframe?
static int isFog = 0;  // fog?
int isOrtho = 1;		// projection mode ?

void Model::loadFile(int argc, char **argv){
	assert(argc == 2);					// check # of arguments
	
	ifstream fileObject(argv[1]);		// object of the file being read
	string fileObjectLine;				// string to save the lines of the file that is being read

	model_list = glGenLists(1);				// init one display list
	glNewList(model_list, GL_COMPILE);		// start of display list

	if (fileObject.is_open()) {
		while (! fileObject.eof() ){
			getline(fileObject, fileObjectLine);

			if (fileObjectLine.c_str()[0] == 'v'){				// if the line starts with 'v', it's declaring a vertice
				//cout << fileObjectLine << endl;
				float x, y, z;
				fileObjectLine[0] = ' ';						// get rid of 'v'
				sscanf(fileObjectLine.c_str(),"%f %f %f ", &x, &y, &z);		// assign the vertice's values to x,y,z
				model_object.vertex_list.push_back(x);						// save the values into the vector vertex_list of
				model_object.vertex_list.push_back(y);						// object model_object
				model_object.vertex_list.push_back(z);
				//cout << "line is " << fileObjectLine << endl;
				//cout << model_object.vertex_list.size() << endl;
				continue;													// skip to next iteration
			}
		}

		// NOTE: this will only run once, after all the vertices have been added and right before polygons/faces are added
		//applyTransfToMatrix();
		model_object.applyTransfToMatrix();

		// go back to beginning of the file
		fileObject.clear();
		fileObject.seekg(0, ios::beg);

		// read file again and process the lines starting with 's'
		while (! fileObject.eof()){
			getline(fileObject, fileObjectLine);
			
			// scanning for 'f' and adding polygons to display list
			if (fileObjectLine.c_str()[0] == 'f'){				// if the line starts with 'f', it's declaring a face/polygon

				s_list.push_back(fileObjectLine);
				fileObjectLine[0] = ' ';			// get rid of 'f' from the line string

				istringstream iss(fileObjectLine);

				glBegin(GL_POLYGON);				// start of polygon
				//cout << "line is : " << fileObjectLine << endl;
				while(iss){
					//count ++;
					int value;
					iss >> value;					// get values one by one
					if (iss.fail()){break;}			// if it fails to get a value, then break out of loop
					glVertex3f(model_object.vertex_list.at(3*(value-1)), model_object.vertex_list.at(3*(value-1) + 1), model_object.vertex_list.at(3*(value-1) + 2));
						// add vertex to the object model_object in vector vertex_list.
				}
				glEnd();							// end of polygon
			}			
		}		
	}
	glEndList();				// end of display list
}

void drawModelTransf(){
   // model
   // apply model translations
   glTranslatef(model_object.model_x, model_object.model_y, model_object.model_z);
	
	// translate to z = -2 so model can rotate about its axis
	glTranslatef(0,0,-2);
	// apply rotation transformations
	glRotatef(model_object.model_rotx,1,0,0);
	glRotatef(model_object.model_roty,0,1,0);
	glRotatef(model_object.model_rotz,0,0,1);
	// translate back to z = 0 where the camera is
	glTranslatef(0,0,2);
}

void drawCameraTransf(){
	// camera
   glTranslatef(camera_object.camera_x, camera_object.camera_y, camera_object.camera_z);
   glRotatef(camera_object.camera_rotx,1,0,0);
   glRotatef(camera_object.camera_roty,0,1,0);
   glRotatef(camera_object.camera_rotz,0,0,1);
}

// Drawing (display) routine.
void drawScene(void)
{
   // Clear screen to background color.
   glClear(GL_COLOR_BUFFER_BIT);

	static int fogMode = GL_LINEAR; // Fog mode
	static float fogStart = 1.0; // Fog start z value.
	static float fogEnd = 5.0; // Fog end z value.
   float fogColor[4] = {1.0, 1.0, 1.0, 0.0};
   // Fog controls.
   if (isFog) glEnable(GL_FOG);
   else glDisable(GL_FOG);
   glHint(GL_FOG_HINT, GL_NICEST);
   glFogfv(GL_FOG_COLOR, fogColor);
   glFogi(GL_FOG_MODE, fogMode);
   glFogf(GL_FOG_START, fogStart);
   glFogf(GL_FOG_END, fogEnd);
	
	// reset transformation matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Set foreground (or drawing) color.
   glColor3f(0.0, 0.0, 0.0);
   
   // wireframe or not?
    if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	// apply translations and rotations to model and camera
	drawCameraTransf();
	drawModelTransf();
	
	// draw display list
   glCallList(model_list);

   // enable double buffer
   glutSwapBuffers();
}

// Initialization routine.
void setup(void) 
{  
   // Set background (or clearing) color.
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   // Set viewport size to be entire OpenGL window.
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   // Set matrix mode to projection.
   glMatrixMode(GL_PROJECTION);
   // Clear current projection matrix to identity.
   glLoadIdentity();

   // Specify the orthographic (or perpendicular) projection, 
   // i.e., define the viewing box.
   if (isOrtho){
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
   }else{
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
   }
   // Set matrix mode to modelview.
   glMatrixMode(GL_MODELVIEW);
   // Clear current modelview matrix to identity.
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
	 // change to wireframe or fill
	  case ' ':
		  if (isWire == 0) {isWire = 1;}
		  else {isWire = 0;}
         glutPostRedisplay();
         break;
	  case 'w':
		  model_object.saveModel();
		  break;
     // enable (F) and disable (f) the fog effect
	  case 'f':
		  isFog = 0;
		  glutPostRedisplay();
		  break;
	  case 'F':
		  isFog = 1;
		  glutPostRedisplay();
		  break;

	// switch between orthographic and perspective projection
	  case 'v':
		  if (isOrtho){}
		  else{
			  isOrtho = 1;
			  glMatrixMode(GL_PROJECTION);
			  glLoadIdentity();
			  glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
			  glutPostRedisplay();
		  }
		  // cout << "ortho enabled !" << endl;
         break;	
	  case 'V':
		  if (isOrtho){
			  isOrtho = 0;
			  glMatrixMode(GL_PROJECTION);
			  glLoadIdentity();
			  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
			  glutPostRedisplay();
		  }
		  // cout << "perspective enabled" << endl;
         break;
     // MODEL TRANSFORMATIONS ----------------------------
	 // start of translating the model (these vars save the state of the model every
	 // 											 turn so when a reset/change of projection is
	 // 											done, all transf. are applied correctly)
	 
	 case 'n':
		  model_object.model_z -= 0.1;
		  glutPostRedisplay();
		  break;
	  case 'N':
		  model_object.model_z += 0.1;
		  glutPostRedisplay();
		  break;
      case 'd':
		  model_object.model_y -= 0.1;
		  glutPostRedisplay();
		  break;
	  case 'D':
		  model_object.model_y += 0.1;
		  glutPostRedisplay();
		  break;
	  case 'l':
		  model_object.model_x -= 0.1;
		  glutPostRedisplay();
		  break;
	  case 'L':
		  model_object.model_x += 0.1;
		  glutPostRedisplay();
		  break;
	  // start of rotating the model (about its center)
	  case 'p':
		  model_object.model_rotx -= 10;
		  if (model_object.model_rotx < 0)
			  model_object.model_rotx = 350;	// set to 350 degrees if angle is < 0
	      glutPostRedisplay();
	      break;
	  case 'P':
		  model_object.model_rotx += 10;
		  if (model_object.model_rotx > 360)
			  model_object.model_rotx = 10;	// set to 10 degrees if angle is < 360
		  glutPostRedisplay();
		  break;
	  case 'y':
		  model_object.model_roty -= 10;
		  if (model_object.model_roty < 0)
			  model_object.model_roty = 350;
	      glutPostRedisplay();
	      break;
	  case 'Y':
		  model_object.model_roty += 10;
		  if (model_object.model_roty > 360)
			  model_object.model_roty = 10;
	      glutPostRedisplay();
	      break;
	  case 'r':
		  model_object.model_rotz -= 10;
		  if (model_object.model_rotz < 0)
			  model_object.model_rotz = 350;
	      glutPostRedisplay();
	      break;
	  case 'R':
		  model_object.model_rotz += 10;
		  if (model_object.model_rotz > 360)
			  model_object.model_rotz = 10;
	      glutPostRedisplay();
	   break;
	  // CAMERA TRANSFORMATIONS ----------------------------
	  // start of translating the camera
	  case 'i':
		  camera_object.camera_z += 0.1;
		  glutPostRedisplay();
		  break;
	  case 'I':
		  camera_object.camera_z -= 0.1;
		  glutPostRedisplay();
		  break;
	   // start of pivoting the camera (about its origin)
	   case 't':
		  camera_object.camera_rotx += 10;
		  if (camera_object.camera_rotx > 360)		// set to 10 degrees if angle is < 360
			  camera_object.camera_rotx = 10;
	      glutPostRedisplay();
	      break;
	  case 'T':
		  camera_object.camera_rotx -= 10;
		  if (camera_object.camera_rotx < 0)
			  camera_object.camera_rotx = 350;			// set to 350 degrees if angle is < 0
		  glutPostRedisplay();
	      break;
	  case 'a':
	      camera_object.camera_roty += 10;
		  if (camera_object.camera_roty > 360)	   // set to 10 degrees if angle is < 360
			  camera_object.camera_roty = 10;
	      glutPostRedisplay();
	      break;
	  case 'A':
		  camera_object.camera_roty -= 10;
	      if (camera_object.camera_roty < 10)
			  camera_object.camera_roty = 350;			// set to 350 degrees if angle is < 0
	      glutPostRedisplay();
	      break;
	  case 'c':
	      camera_object.camera_rotz += 10;
		  if (camera_object.camera_rotz > 360)
			  camera_object.camera_rotz = 10;
	      glutPostRedisplay();
	      break;
	  case 'C':
		  camera_object.camera_rotz -= 10;
	      if (camera_object.camera_rotz < 0)
			  camera_object.camera_rotz = 350;
	      glutPostRedisplay();
	      break;

	 // reset model (s) or quit (q)
	  case 's':
	    // reset all model variables
		 model_object.resetVars();
		 // reset all camera variables
		 camera_object.resetVars();
		 
		 // refresh..
		 glutPostRedisplay();
         break;
      case 'q':
         exit(0);
         break;
      default:
         break;
   }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	// start of Translating Camera
	if(key == GLUT_KEY_UP){
		camera_object.camera_y -= 0.1;
		glutPostRedisplay();
	} 
   
	if(key == GLUT_KEY_DOWN) {
	    camera_object.camera_y += 0.1;
		glutPostRedisplay();
	}

	if(key == GLUT_KEY_LEFT){
		camera_object.camera_x += 0.1;
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_RIGHT){
		camera_object.camera_x -= 0.1;
		glutPostRedisplay();
	}
	// end of Translating Camera   
}

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  
   // Initialize GLUT.
   glutInit(&argc, argv);
   // Set display mode as single-buffered and RGB color.
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   // Set OpenGL window size.
   glutInitWindowSize(500, 500);	
   // Set position of OpenGL window upper-left corner.
   glutInitWindowPosition(100, 100); 
   // Create OpenGL window with title.
   glutCreateWindow("Model.cpp");
   
   // load the model
   model_object.loadFile(argc, argv);
   
   // Initialize.
   setup(); 
   // Register display routine.
   glutDisplayFunc(drawScene); 
   // Register reshape routine.
   glutReshapeFunc(resize);  
   // Register keyboard routine.
   glutKeyboardFunc(keyInput);
   // Register the callback function for non-ASCII key entry.
   glutSpecialFunc(specialKeyInput);
      
   // Begin processing.
   glutMainLoop(); 

   return 0;  
}

