/*
 * BVH.cpp
 *
 *
 */
#include <algorithm>
#include "BVH.h"


namespace rt{

    void BVH::computeBBox(std::vector<Shape>* shapes, int startIndex, int endIndex) {
        // compute bounding box
        bbox.inUse = true;
        for (int i = startIndex; i < endIndex; i++) {

            BoundingBox b = shapes->at(i).getBBox();

            if (b.x0 < bbox.x0) bbox.x0 = b.x0;
            if (b.y0 < bbox.y0) bbox.y0 = b.y0;
            if (b.z0 < bbox.z0) bbox.z0 = b.z0;

            if (b.x1 > bbox.x1) bbox.x1 = b.x1;
            if (b.y1 > bbox.y1) bbox.y1 = b.y1;
            if (b.z1 > bbox.z1) bbox.z1 = b.z1;
        }

    }

    BVH::BVH(std::vector<Shape>* shapes, int startIndex, int endIndex, BlinnPhong* mat) {
        material = mat;
        computeBBox(shapes, startIndex, endIndex);

        int sliceSize = endIndex - startIndex;

        // If we have reached the bottom, just put the primitive as both leaves
        if (sliceSize == 1) {
            lChild = &shapes->at(startIndex);
            rChild = &shapes->at(startIndex);
        } else {
            // Pick a random axis and sort shapes list by bbox.[axis]0
            int randomAxis = std::rand() % 3;
            switch(randomAxis) {
                case 0:
                    std::sort(startIndex, endIndex, [](Shape& s1, Shape& s2){return s1.getBBox().x0 < s2.getBBox().x0;});
                    break;
                case 1:
                    std::sort(startIndex, endIndex, [](Shape& s1, Shape& s2){return s1.getBBox().y0 < s2.getBBox().y0;});
                    break;
                case 2:
                    std::sort(startIndex, endIndex, [](Shape& s1, Shape& s2){return s1.getBBox().z0 < s2.getBBox().z0;});
                    break;
                default:
                    std::cerr<<"You're a wizard"<<std::endl;
                    exit(-1);
            }

            int sliceMidpoint = startIndex + (sliceSize/2);
            lChild = new BVH(shapes, startIndex, sliceMidpoint, material);
            rChild = new BVH(shapes, sliceMidpoint, endIndex, material);
        }





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

        if (t_x0 < 0 || t_x1 < 0) return false;

        float t_y0 = (bbox.y0 - ray.o.y) / ray.d.y;
        float t_y1 = (bbox.y1 - ray.o.y) / ray.d.y;
        if (t_y1 < t_y0) std::swap(t_y0, t_y1);

        if (t_y0 < 0 || t_y1 < 0) return false;

        float t_z0 = (bbox.z0 - ray.o.z) / ray.d.z;
        float t_z1 = (bbox.z1 - ray.o.z) / ray.d.z;
        if (t_z1 < t_z0) std::swap(t_z0, t_z1);

        if (t_z0 < 0 || t_z1 < 0) return false;

        float maxOfMins = std::max(t_x0, std::max(t_y0, t_z0));
        float minOfMaxes = std::min(t_x1, std::min(t_y1, t_z1));

        // If maxOfMins < minOfMaxes then there should be an overlap
        return (maxOfMins < minOfMaxes);
    }

    Hit BVH::intersect(Ray ray) {
        if (intersectsBBox(ray)) {
            Hit h1 = lChild->intersect(ray);
            Hit h2 = rChild->intersect(ray);
            if (h1.hit && h2.hit) {
                return ((h1.point-ray.o).length() < (h2.point-ray.o).length()) ? h1 : h2;
            } else if (h1.hit) {
                return h1;
            } else if (h2.hit) {
                return h2;
            }
        }
        Hit blankHit;
        return blankHit;
    }


} //namespace rt


