
#ifndef PLYREADER_H_
#define PLYREADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "math/geometry.h"
#include "shapes/Triangle.h"


namespace PLYReader{

	std::vector<rt::Shape*>* PLYReader(const std::string& filename);

};



#endif /* PLYREADER_H_ */
