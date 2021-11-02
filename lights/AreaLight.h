/*
 * AreaLight.h
 *
 *
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "core/LightSource.h"

namespace rt{

class AreaLight:public LightSource {

public:
    AreaLight(Vec3f position, Vec3f specular_intensity, Vec3f diffuse_intensity)
            : LightSource{position, specular_intensity, diffuse_intensity} {}

    void print();
};


} //namespace rt




#endif /* AREALIGHT_H_ */
