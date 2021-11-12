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

// A TriMesh object should never be added to the scene on its own
// Instead, a BVH object should be created that encompasses the trimesh
// Otherwise, there will be no optimisation and the render will be slow

class TriMesh: public Shape{

public:

    TriMesh(const std::string& filename, BlinnPhong* mat);

    ~TriMesh() override {}

    Hit intersect(Ray) override;

    std::vector<Triangle>& getTriangles() {
        return *m_triangles;
    }

private:

    std::vector<Triangle>* m_triangles;


};



} //namespace rt




#endif /* TRIMESH_H_ */
