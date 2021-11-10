/*
 * BlinnPhong.h
 *
 *
 */

#ifndef BLINNPHONG_H_
#define BLINNPHONG_H_

#include <geometry.h>
#include "parsers/PPMReader.h"
#include "PPMReader.h"
#include "core/Material.h"


namespace rt{

class BlinnPhong: public Material{

public:

    BlinnPhong() = default;

    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor, std::string &tPath, int tWidth, int tHeight)
        : m_ks{ks}, m_kd{kd}, m_kr{kr}, m_specularexponent{specularexponent}, m_diffusecolor{diffusecolor}, m_tPath{tPath}, m_tWidth{tWidth}, m_tHeight{tHeight}, m_texture{
            PPMReader::PPMReader(tWidth, tHeight, tPath)} {}

    BlinnPhong(float ks, float kd, float kr, int specularexponent, Vec3f diffusecolor)
            : m_ks{ks}, m_kd{kd}, m_kr{kr}, m_specularexponent{specularexponent}, m_diffusecolor{diffusecolor}, m_tPath{"none"}, m_tWidth{0}, m_tHeight{0}, m_texture{nullptr} {}

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

    int getTWidth() const {
        return m_tWidth;
    }

    int getTHeight() const {
        return m_tHeight;
    }

    Vec3f *getTexture() const {
        return m_texture;
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
    Vec3f* m_texture;

};



} //namespace rt



#endif /* BLINNPHONG_H_ */
