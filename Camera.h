/* Class Model */
 #ifndef Camera_H
#define Camera_H

#include <vector>
#include <string>
#include <fstream>

/* Class Camera */
 
class Camera
{
public: 	

	void resetVars();
		
	float camera_x;
	float camera_y;
	float camera_z;

	float camera_rotx;
	float camera_roty;
	float camera_rotz;
};

#endif
