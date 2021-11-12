/*
 * Triangle.h
 *
 *
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "core/Shape.h"
#include "materials/BlinnPhong.h"

namespace rt{

class Triangle: public Shape {

public:
    Triangle() = default;
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, BlinnPhong* mat);

    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec2f uv0, Vec2f uv1 ,Vec2f uv2, BlinnPhong* mat);

    Hit intersect(Ray r) override;

    ~Triangle() override {
//        std::cout << "Destroyed triangle!" << std::endl;
    }

    void computeBBox();

    const Vec3f &getV0() const {
        return m_v0;
    }

    const Vec3f &getV1() const {
        return m_v1;
    }

    const Vec3f &getV2() const {
        return m_v2;
    }

    void print();

private:
    Vec3f m_v0;
    Vec3f m_v1;
    Vec3f m_v2;
    Vec2f m_uv0;
    Vec2f m_uv1;
    Vec2f m_uv2;
    Vec3f normal;
};



}; //namespace rt




#endif /* TRIANGLE_H_ */
