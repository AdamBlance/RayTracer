/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

TriMesh::TriMesh(const std::string &filename, BlinnPhong* mat) {
    material = mat;
    m_triangles = PLYReader::PLYReader(filename);

    // compute bounding box
    bbox.inUse = true;
    for (auto& tri : *m_triangles) {
        auto v0 = tri.getV0();
        auto v1 = tri.getV1();
        auto v2 = tri.getV2();

        float xMin = std::min(v0.x, std::min(v1.x, v2.x));
        if (xMin < bbox.x0) bbox.x0 = xMin;
        float xMax = std::max(v0.x, std::max(v1.x, v2.x));
        if (xMax > bbox.x1) bbox.x1 = xMax;
        float yMin = std::min(v0.y, std::min(v1.y, v2.y));
        if (yMin < bbox.y0) bbox.y0 = yMin;
        float yMax = std::max(v0.y, std::max(v1.y, v2.y));
        if (yMax > bbox.y1) bbox.y1 = yMax;
        float zMin = std::min(v0.z, std::min(v1.z, v2.z));
        if (zMin < bbox.z0) bbox.z0 = zMin;
        float zMax = std::max(v0.z, std::max(v1.z, v2.z));
        if (zMax > bbox.z1) bbox.z1 = zMax;
    }
}

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


