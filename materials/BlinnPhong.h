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
    BlinnPhong(float ks, float kd, int specularexponent, Vec3f diffusecolor, std::string &tPath, int tWidth, int tHeight)
        : m_ks{ks}, m_kd{kd}, m_specularexponent{specularexponent}, m_diffusecolor{diffusecolor}, m_tPath{tPath}, m_tWidth{tWidth}, m_tHeight{tHeight} {}


private:
    float m_ks;
    float m_kd;
    int m_specularexponent;
    Vec3f m_diffusecolor;
    std::string m_tPath;
    int m_tWidth;
    int m_tHeight;

};



} //namespace rt



#endif /* BLINNPHONG_H_ */
