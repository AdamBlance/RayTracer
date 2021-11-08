//
// Created by Adam on 08/11/2021.
//

#ifndef RAY_TRACER_HELPER_H
#define RAY_TRACER_HELPER_H


#include <geometry.h>
#include "rapidjson/document.h"


class Helper {

public:
    static Vec3f toVec3f(const rapidjson::Value& json_array);
};


#endif //RAY_TRACER_HELPER_H
