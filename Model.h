/* Class Model */
 #ifndef Model_H
#define Model_H

#include <vector>
#include <string>
#include <fstream>

/* Class Model */
 
class Model
{
public: 		
   void loadFile(int argc, char **argv);		// load model coords from file
	void saveModel();
	void resetVars();
	void calculateVertex();
	void getMaxMins();
	void applyTransfToMatrix();
	
	//vectors
	std::vector<float> vertex_list;
	std::vector<std::string> s_list;
	float mean_x;
	float mean_y;
	float mean_z;

	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float max_z;
	float min_z;

	float max_scale;

	float model_x;
	float model_y;
	float model_z;

	float model_rotx;
	float model_roty;
	float model_rotz;

};

#endif
