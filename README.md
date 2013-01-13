3D_model_viewer
===============

3D model viewer for .OBJ files in C++ / OpenGL

-------
Windows:

  By using Microsoft Visual C++:
  
  -> create new project (Win32 Console App) -> add main.cpp to 'Source Files' and the others to 'Header Files'
    
  -> To feed an .obj file, go to Project -> Properties -> Configuration Properties -> Debugging -> Fill in command arguments.. (ex. skull.obj)

-------
Linux:   ( requires opengl libs )

  Use the makefile provided (type 'make').
  
  run with 1 argument ( the .OBJ file ), example:
  
  ./modelviewer filename.obj

---------------------
Model Viewer Commands

character 'v' sets the viewing projection to orthographic
character 'V' sets the viewing projection to perspective

character 'w' outputs the object to a file 'output.OBJ'

character 's' reset the model and camera to their default position and orientation
character 'q' exits the application

Translating the model:

  'l'     -0.1 translation along x-axis
  'L'      0.1 translation along x-axis
    
  'd'     -0.1 translation along y-axis
  'D'      0.1 translation along y-axis
    
  'n'     -0.1 translation along z-axis
  'N'      0.1 translation along z-axis
    
Rotating the model:

  'p'      rotate the model -10 degrees CCW around the x-axis (centered at model's center)  (pitch)
  'P'      rotate the model  10 degrees CCW around the x-axis (centered at model's center)  (pitch)
    
  'y'      rotate the model -10 degrees CCW around the y-axis (centered at model's center)  (yaw)
  'Y'      rotate the model  10 degrees CCW around the y-axis (centered at model's center)  (yaw)
    
  'n'      rotate the model -10 degrees CCW around the z-axis (centered at model's center)  (roll)
  'N'      rotate the model  10 degrees CCW around the z-axis (centered at model's center)  (roll)
  
Translating the camera:

  <leftarrow>    translate the camera -0.1 units along the x-axis (dolly)
  <rightarrow>   translate the camera  0.1 units along the x-axis (dolly)

  <downarrow>    translate the camera -0.1 units along the y-axis (crane)
  <uparrow>      translate the camera  0.1 units along the y-axis (crane)

  'i'       translate the camera -0.1 units along the z-axis (zoom)
  'I'       translate the camera -0.1 units along the z-axis (zoom)
 
Pivot the camera (about its origin):

  't'       rotate the camera -10 degrees CCW around its x-axis (centered at camera's origin) (tilt)
  'T'       rotate the camera  10 degrees CCW around its x-axis (centered at camera's origin) (tilt)

  'a'       rotate the camera -10 degrees CCW around its y-axis (centered at camera's origin) (pan)
  'A'       rotate the camera  10 degrees CCW around its y-axis (centered at camera's origin) (pan)
  
  'c'       rotate the camera -10 degrees CCW around its z-axis (centered at camera's origin) (tilt)
  'C'       rotate the camera  10 degrees CCW around its z-axis (centered at camera's origin) (tilt)
  
