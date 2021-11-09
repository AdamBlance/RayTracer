//
// Created by Adam on 08/11/2021.
//

#ifndef PLANE_H_
#define PLANE_H_

#include <core/Shape.h>
#include "geometry.h"
#include "Triangle.h"

namespace rt{

class Plane: public Shape {
public:

    Plane(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v0);

    Hit intersect(Ray ray) override;

private:
    Vec3f m_v0;
    Vec3f m_v1;
    Vec3f m_v2;
    Vec3f m_v3;

    Triangle tri1;
    Triangle tri2;

};




}; //namespace rt


#endif //RAY_TRACER_PLANE_H
