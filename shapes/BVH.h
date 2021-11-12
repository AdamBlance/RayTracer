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

    BVH(std::vector<Shape*>* shapes, int startIndex, int endIndex, BlinnPhong* mat);

    Hit intersect(Ray ray) override;

private:

    bool intersectsBBox(Ray ray);

    void computeBBox(std::vector<Shape*>* shapes, int startIndex, int endIndex);

    Shape* lChild;
    Shape* rChild;


};



} //namespace rt



#endif /* BVH_H_ */
