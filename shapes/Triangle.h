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

    Hit intersect(Ray r) override;

    ~Triangle() override {
//        std::cout << "Destroyed triangle!" << std::endl;
    }

    void print();

private:
    Vec3f m_v0;
    Vec3f m_v1;
    Vec3f m_v2;
    Vec3f normal;
};



}; //namespace rt




#endif /* TRIANGLE_H_ */
