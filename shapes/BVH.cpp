/*
 * BVH.cpp
 *
 *
 */
#include <algorithm>
#include "BVH.h"


namespace rt{

    static bool

    BVH::BVH(TriMesh* trimesh)
        : Shape(trimesh->getMaterial()) {

        auto& tris = trimesh->getTriangles();

        auto sortComparator = [](Shape& shape1)

        std::sort(tris.begin(), tris.end(), )

    }



    bool BVH::intersectsBBox(Ray ray) {

        // r(t) = r.o + t*r.d
        // Need to find intersections of ray with bounding box
        // Since boxes are axis-aligned, we don't need to worry about planes or anything
        // Instead solve for when r(t) = x0 and r(t) = x1
        // x0 = r.o.x + t*r.d.x
        // t = x0 - r.o.x / r.d.x
        // Do this for all axes and check if t-ranges overlap

        // If rays are coming from behind, v_x1 might be less than v_x0 which is not ideal
        // we just need to do max and min

        float t_x0 = (bbox.x0 - ray.o.x) / ray.d.x;
        float t_x1 = (bbox.x1 - ray.o.x) / ray.d.x;
        if (t_x1 < t_x0) std::swap(t_x0, t_x1);

        float t_y0 = (bbox.y0 - ray.o.y) / ray.d.y;
        float t_y1 = (bbox.y1 - ray.o.y) / ray.d.y;
        if (t_y1 < t_y0) std::swap(t_y0, t_y1);

        float t_z0 = (bbox.z0 - ray.o.z) / ray.d.z;
        float t_z1 = (bbox.z1 - ray.o.z) / ray.d.z;
        if (t_z1 < t_z0) std::swap(t_z0, t_z1);

        float maxOfMins = std::max(t_x0, std::max(t_y0, t_z0));
        float minOfMaxes = std::min(t_x1, std::min(t_y1, t_z1));

        // If maxOfMins < minOfMaxes then there should be an overlap
        return (maxOfMins < minOfMaxes);
    }

    Hit BVH::intersect(Ray ray) {
        if (intersectsBBox(ray)) {
            return child->intersect(ray);
        }
        Hit blankHit;
        return blankHit;
    }


} //namespace rt


