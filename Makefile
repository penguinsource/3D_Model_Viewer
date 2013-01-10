modelviewer: mainModel.o ModelSet.o CameraSet.o
	g++ $(CFLAGS) -Wall -o modelviewer mainModel.o ModelSet.o CameraSet.o -I/usr/include -L/usr/lib -lglut -lGL -lGLU -lX11

mainModel.o: main.cpp Model.h Camera.h
	g++ $(CFLAGS) -Wall -o mainModel.o -c main.cpp 

ModelSet.o: Model.cpp Model.h
	g++ $(CFLAGS) -Wall -c Model.cpp -o ModelSet.o

CameraSet.o: Camera.cpp Camera.h
	g++ $(CFLAGS) -Wall -c Camera.cpp -o CameraSet.o

