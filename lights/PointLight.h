/*
 * PointLight.h
 *
 *
 */

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "core/LightSource.h"


namespace rt{

class PointLight: public LightSource{

public:

    PointLight(Vec3f position, Vec3f specular_intensity, Vec3f diffuse_intensity)
        : LightSource{position, specular_intensity, diffuse_intensity} {}

    void print();

};



} //namespace rt




#endif /* POINTLIGHT_H_ */
