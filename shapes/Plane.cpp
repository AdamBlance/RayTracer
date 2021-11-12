//
// Created by Adam on 08/11/2021.
//

#include "Plane.h"
#include "Triangle.h"

namespace rt{

    Plane::Plane(Vec3f v1, Vec3f v2, Vec3f v3, Vec3f v0, BlinnPhong* mat) {
        material = mat;
        m_v1 = v1;
        m_v2 = v2;
        m_v3 = v3;
        m_v0 = v0;

        tri1 = Triangle(
                m_v3, m_v2, m_v1,                                            // points
                Vec2f(0,1), Vec2f(1,1), Vec2f(1,0),  // uv-coords
                material);
        tri2 = Triangle(
                m_v1, m_v0, m_v3,
                Vec2f(1,0), Vec2f(0, 0), Vec2f(0, 1),
                material);

        // compute bbox

        bbox.inUse = true;

        auto bbox1 = tri1.getBBox();
        auto bbox2 = tri2.getBBox();

        bbox.x0 = std::min(bbox1.x0, bbox2.x0);
        bbox.y0 = std::min(bbox1.y0, bbox2.y0);
        bbox.z0 = std::min(bbox1.z0, bbox2.z0);

        bbox.x1 = std::max(bbox1.x1, bbox2.x1);
        bbox.y1 = std::max(bbox1.y1, bbox2.y1);
        bbox.z1 = std::max(bbox1.z1, bbox2.z1);

    }


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
