3D_model_viewer
===============

3D model viewer for .OBJ files in C++ / OpenGL

Windows:
  By using Microsoft Visual C++
    -> create new project (Win32 Console App) -> add main.cpp to 'Source Files' and the others to 'Header Files'
    -> To feed an .obj file, go to Project -> Properties -> Configuration Properties -> Debugging -> Fill in command arguments.. (ex. skull.obj)

Linux:   ( requires opengl libs )
  Use the makefile provided (type 'make').
  run with 1 argument ( the .OBJ file ), example:
    ./modelviewer skull.obj

