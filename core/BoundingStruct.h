//
// Created by Adam on 12/11/2021.
//

#ifndef CORE_BOUNDINGSTRUCTS_H_
#define CORE_BOUNDINGSTRUCTS_H_

#include <limits>

struct BoundingBox {

    bool inUse = false;

    float x0 = std::numeric_limits<float>::max();
    float x1 = std::numeric_limits<float>::min();

    float y0 = std::numeric_limits<float>::max();
    float y1 = std::numeric_limits<float>::min();

    float z0 = std::numeric_limits<float>::max();
    float z1 = std::numeric_limits<float>::min();

};

#endif //CORE_BOUNDINGSTRUCTS_H_
