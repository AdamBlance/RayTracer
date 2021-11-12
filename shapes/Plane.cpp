//
// Created by Adam on 08/11/2021.
//

#include "Plane.h"
#include "Triangle.h"

namespace rt{


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

    BoundingBox Plane::getBBox() {
        return bbox;  // Returns bounding box with default value inUse=false
    }

} //namespace rt
