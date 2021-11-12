/*
 * BVH.h
 *
 *
 */

#ifndef BVH_H_
#define BVH_H_

#include "core/Shape.h"
#include "TriMesh.h"

namespace rt{

class BVH: public Shape{

public:

    BVH(TriMesh* shape)
        : Shape(shape->getMaterial()), bbox{shape->getBBox()}, child{shape} {};

    Hit intersect(Ray ray) override;

    bool intersectsBBox(Ray ray);

private:

    BoundingBox bbox;
    TriMesh* child;


};



} //namespace rt



#endif /* BVH_H_ */
