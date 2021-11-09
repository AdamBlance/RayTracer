/*
 * LightSource.h
 *
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "math/geometry.h"

namespace rt{

class LightSource{
public:

    LightSource(Vec3f position, Vec3f specular_intensity, Vec3f diffuse_intensity)
        : m_position{position}, m_specular_intensity{specular_intensity}, m_diffuse_intensity{diffuse_intensity} {}

    const Vec3f &getPosition() const {
        return m_position;
    }

    const Vec3f &getSpecularIntensity() const {
        return m_specular_intensity;
    }

    const Vec3f &getDiffuseIntensity() const {
        return m_diffuse_intensity;
    }

private:

    Vec3f m_position;
    Vec3f m_specular_intensity;
    Vec3f m_diffuse_intensity;

};

} //namespace rt



#endif /* LIGHTSOURCE_H_ */
