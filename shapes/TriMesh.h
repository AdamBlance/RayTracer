/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include <vector>
#include "core/Shape.h"
#include "shapes/Triangle.h"
#include "parsers/PLYReader.h"

namespace rt{

class TriMesh: public Shape{

public:

    TriMesh(const std::string& filename, BlinnPhong mat)
        : Shape(mat), m_triangles{PLYReader::PLYReader(filename)} {}

    ~TriMesh() override {}

    Hit intersect(Ray) override;

    BoundingBox getBBox();


private:

    std::vector<Triangle>* m_triangles;


};



} //namespace rt




#endif /* TRIMESH_H_ */
