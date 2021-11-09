/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include <geometry.h>
#include "core/Material.h"


namespace rt{

class BlinnPhong: public Material{

public:

    BlinnPhong() = default;

    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor, std::string &tPath, int tWidth, int tHeight)
        : m_ks{ks}, m_kd{kd}, m_kr{kr}, m_specularexponent{specularexponent}, m_diffusecolor{diffusecolor}, m_tPath{tPath}, m_tWidth{tWidth}, m_tHeight{tHeight} {}

    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor)
            : m_ks{ks}, m_kd{kd}, m_kr{kr}, m_specularexponent{specularexponent}, m_diffusecolor{diffusecolor}, m_tWidth{0}, m_tHeight{0} {}

    float getKs() const {
        return m_ks;
    }

    float getKd() const {
        return m_kd;
    }

    float getKr() const {
        return m_kr;
    }

    int getSpecularexponent() const {
        return m_specularexponent;
    }

    Vec3f getDiffusecolor() const {
        return m_diffusecolor;
    }

    std::string getTPath() const {
        return m_tPath;
    }

    int getMTWidth() const {
        return m_tWidth;
    }

    int getMTHeight() const {
        return m_tHeight;
    }

private:
    float m_ks;
    float m_kd;
    float m_kr;
    int m_specularexponent;
    Vec3f m_diffusecolor;
    std::string m_tPath;
    int m_tWidth;
    int m_tHeight;

};



} //namespace rt



#endif /* BLINNPHONG_H_ */
