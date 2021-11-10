//
// Created by Adam on 08/11/2021.
//

#include "Plane.h"
#include "Triangle.h"

namespace rt{

//    Plane::Plane(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v0, BlinnPhong mat) {
//
//        m_v1 = v1;
//        m_v2 = v2;
//        m_v3 = v3;
//        m_v0 = v0;
//
//        tri1 = Triangle(m_v1, m_v2, m_v3);
//        tri2 = Triangle(m_v3, m_v0, m_v1);
//
//    };


    Hit Plane::intersect(Ray ray) {

        Hit hit1 = tri1.intersect(ray);
        Hit hit2 = tri2.intersect(ray);

        Hit h;

        if (hit1.hit) {
            h = hit1;
        } else if (hit2.hit) {
            h =  hit2;
        } else {
            Hit blankHit;
            return blankHit;
        }

        return h;
    }

} //namespace rt
