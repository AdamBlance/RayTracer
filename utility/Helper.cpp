//
// Created by Adam on 08/11/2021.
//

#include "Helper.h"

// Converts json array to vec3f
Vec3f Helper::toVec3f(const rapidjson::Value& json_array) {
    Vec3f v(json_array[0].GetFloat(), json_array[1].GetFloat(), json_array[2].GetFloat());
    return v;
}