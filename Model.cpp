#include "Model.h"

void Model::resetVars(){
	this->model_x = 0;
	this->model_y = 0;
	this->model_z = 0;
	this->model_rotx = 0;
	this->model_roty = 0;
	this->model_rotz = 0;
}

void Model::saveModel(){
   std::ofstream saveObj;
	saveObj.open("output.obj");
	
	// go through each vertice and push it to file 'output.obj'
	for (unsigned int h = 0; h < this->vertex_list.size(); h += 3){
		saveObj << "v " << this->vertex_list.at(h) << " " <<
			this->vertex_list.at(h+1) << " " << this->vertex_list.at(h+2) << std::endl;
	}
	// go through each 's' polygon and push it to file 'output.obj' (s_list contains a list of strings)
	for (unsigned int h =0; h < this->s_list.size(); h++){
		saveObj << this->s_list.at(h) << std::endl;
	}
}

void Model::calculateVertex(){
	this->mean_x = 0;
	this->mean_y = 0;
	this->mean_z = 0;

	for (int q = 0; q < (this->vertex_list.size() / 3) ; q++){
		//cout << model_object.vertex_list.at(q) << endl;
		this->mean_x += this->vertex_list.at(3*q);
	}

	for (int q = 0; q < (this->vertex_list.size() / 3) ; q++){
		//cout << model_object.vertex_list.at(q) << endl;
		this->mean_y += this->vertex_list.at(3*q + 1);
	}

	for (int q = 0; q < (this->vertex_list.size() / 3) ; q++){
		//cout << model_object.vertex_list.at(q) << endl;
		this->mean_z += this->vertex_list.at(3*q+2);
	}

	this->mean_x = this->mean_x / (this->vertex_list.size() / 3);
	this->mean_y = this->mean_y / (this->vertex_list.size() / 3);
	this->mean_z = this->mean_z / (this->vertex_list.size() / 3);
}

void Model::getMaxMins(){
	this->max_x = this->vertex_list.at(0);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q) > this->max_x){
			this->max_x = this->vertex_list.at(3*q);
		}
	}

	this->min_x = this->vertex_list.at(0);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q) < this->min_x){
			this->min_x = this->vertex_list.at(3*q);
		}
	}

	this->max_y = this->vertex_list.at(1);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q + 1) > this->max_y){
			this->max_y = this->vertex_list.at(3*q + 1);
		}
	}

	this->min_y = this->vertex_list.at(1);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q + 1) < this->min_y){
			this->min_y = this->vertex_list.at(3*q + 1);
		}
	}

	this->max_z = this->vertex_list.at(2);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q + 2) > this->max_z){
			this->max_z = this->vertex_list.at(3*q + 2);
		}
	}

	this->min_z = this->vertex_list.at(2);
	for (int q = 0; q < ( this->vertex_list.size() / 3 ); q++){
		if (this->vertex_list.at(3*q + 2) < this->min_z){
			this->min_z = this->vertex_list.at(3*q + 2);
		}
	}

	float scale_x = this->max_x - this->min_x;
	float scale_y = this->max_y - this->min_y;
	float scale_z = this->max_z - this->min_z;

	this->max_scale = scale_x;					//get the max scale
	if (scale_y > this->max_scale)			//the scale is max(xmax - xmin, ymax -ymin, zmax -zmin)
		this->max_scale = scale_y;

	if (scale_z > this->max_scale)
		this->max_scale = scale_z;
}

void Model::applyTransfToMatrix(){
   this->calculateVertex();
   this->getMaxMins();

	// translate all vertices by substracting them by their means
   
   for (unsigned int h = 0; h < ( this->vertex_list.size() / 3); h++){					// substract each x  of each vertice by mean x
	   this->vertex_list.at(3*h) = this->vertex_list.at(3*h) - this->mean_x;
   }
   for (unsigned int h = 0; h < ( this->vertex_list.size() / 3); h++){
	   this->vertex_list.at(3*h + 1) = this->vertex_list.at(3*h + 1) - this->mean_y;
   }
   
   for (unsigned int h = 0; h < ( this->vertex_list.size() / 3); h++){
	   this->vertex_list.at(3*h + 2) = this->vertex_list.at(3*h + 2) - this->mean_z;
   }
   //calculateVertex();
   for (unsigned int h = 0; h < this->vertex_list.size() ; h++){							// scale every coordinate in the vector object
	   this->vertex_list.at(h) = this->vertex_list.at(h) / this->max_scale;
   }   
   
   for (unsigned int h = 0; h < (this->vertex_list.size() / 3); h++){					// this is a translation of (0,0,-2)
	   this->vertex_list.at(3*h + 2) -= 2;									// equivalent to glTranslatef(0,0,-2) but applied
   }	

}

