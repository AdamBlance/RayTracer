//
// Created by Adam on 08/11/2021.
//

#ifndef PLANE_H_
#define PLANE_H_

#include <core/Shape.h>
#include "geometry.h"
#include "Triangle.h"
#include "materials/BlinnPhong.h"

namespace rt{

class Plane: public Shape {
public:

    Plane(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v0, BlinnPhong mat)
        : Shape(mat), m_v1{v1}, m_v2{v2}, m_v3{v3}, m_v0{v0}, tri1{Triangle(m_v3, m_v2, m_v1, Vec2f(0,1), Vec2f(1,1), Vec2f(1,0), mat)}, tri2{Triangle(m_v1, m_v0, m_v3, Vec2f(1,0), Vec2f(0, 0), Vec2f(0, 1), mat)} {};

    Hit intersect(Ray ray) override;

private:
    Vec3f m_v1;
    Vec3f m_v2;
    Vec3f m_v3;
    Vec3f m_v0;

    Triangle tri1;
    Triangle tri2;

};




}; //namespace rt


#endif //RAY_TRACER_PLANE_H
