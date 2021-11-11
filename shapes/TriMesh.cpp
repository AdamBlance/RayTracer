/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{


Hit TriMesh::intersect(Ray ray) {

    Hit h;

    float minDist = 1000000;

    for (auto& triangle : *m_triangles) {
        Hit triHit = triangle.intersect(ray);
        if (triHit.hit) {
            float dist = (triHit.point - ray.o).length();
            if (dist < minDist) {
                minDist = dist;
                h = triHit;
            }
        }
    }

    return h;

}


} //namespace rt


