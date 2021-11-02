/*
 * TriMesh.h
 *
 *
 */

#ifndef TRIMESH_H_
#define TRIMESH_H_

#include "core/Shape.h"
#include "shapes/Triangle.h"

namespace rt{

class TriMesh: public Shape{

public:

    TriMesh(Vec3f triangles[])
        : m_triangles{triangles} {}

    ~TriMesh() override {}

    Hit intersect(Ray) override;



private:

    Vec3f *m_triangles[];

};



} //namespace rt




#endif /* TRIMESH_H_ */
