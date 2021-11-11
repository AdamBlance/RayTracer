
#ifndef PPMREADER_H_
#define PPMREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "math/geometry.h"


namespace PPMReader{

	Vec3f* PPMReader(int width,int height, const std::string& filename);

};



#endif /* PPMREADER_H_ */
