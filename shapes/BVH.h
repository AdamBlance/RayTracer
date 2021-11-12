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

    explicit BVH(TriMesh* triMesh);
    BVH(std::vector<Shape>* shapes, int startIndex, int endIndex);

    Hit intersect(Ray ray) override;

    BoundingBox getBBox() override;

    bool intersectsBBox(Ray ray);

private:

    BoundingBox bbox;

    BVH* lChild;
    BVH* rChild;


};



} //namespace rt



#endif /* BVH_H_ */
