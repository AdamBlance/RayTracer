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
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, BlinnPhong mat)
            : Shape(mat), m_v0{v0}, m_v1{v1}, m_v2{v2}, normal{((m_v1-m_v0).crossProduct(m_v2-m_v1)).normalize()} {
//        std::cout << "Created triangle!" << std::endl;
//        print();
    };
    Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec2f uv0, Vec2f uv1 ,Vec2f uv2, BlinnPhong mat)
            : Shape(mat), m_v0{v0}, m_v1{v1}, m_v2{v2}, m_uv0{uv0}, m_uv1{uv1}, m_uv2{uv2}, normal{((m_v1-m_v0).crossProduct(m_v2-m_v1)).normalize()} {
//        std::cout << "Created triangle!" << std::endl;
//        print();
    };

    Hit intersect(Ray r) override;

    ~Triangle() override {
//        std::cout << "Destroyed triangle!" << std::endl;
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
