/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

    static double det2(float a, float b, float c, float d) {
        return a*d - b*c;
    }

    static double det3(Vec3f col1, Vec3f col2, Vec3f col3) {
        double term1 = col1[0] * det2(col2[1], col3[1], col2[2], col3[2]);
        double term2 = col2[0] * det2(col1[1], col3[1], col1[2], col3[2]);
        double term3 = col3[0] * det2(col1[1], col2[1], col1[2], col2[2]);
        return term1 - term2 + term3;
    }

    static Vec3f cramers(Vec3f Acol1, Vec3f Acol2, Vec3f Acol3, Vec3f B) {
        Vec3f x;

        double Adet = det3(Acol1, Acol2, Acol3);

        x[0] = det3(B, Acol2, Acol3) / Adet;
        x[1] = det3(Acol1, B, Acol3) / Adet;
        x[2] = det3(Acol1, Acol2, B) / Adet;

        return x;
    }

    void Triangle::computeBBox() {
        bbox.inUse = true;

        // Slightly nicer naming
        auto& v0 = m_v0;
        auto& v1 = m_v1;
        auto& v2 = m_v2;

        bbox.x0 = std::min(v0.x, std::min(v1.x, v2.x));
        bbox.x1 = std::max(v0.x, std::max(v1.x, v2.x));

        bbox.y0 = std::min(v0.y, std::min(v1.y, v2.y));
        bbox.y1 = std::max(v0.y, std::max(v1.y, v2.y));

        bbox.z0 = std::min(v0.z, std::min(v1.z, v2.z));
        bbox.z1 = std::max(v0.z, std::max(v1.z, v2.z));
    }

    Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2, BlinnPhong* mat) {
        material = mat;
        m_v0 = v0;
        m_v1 = v1;
        m_v2 = v2;
        normal = (m_v1-m_v0).crossProduct(m_v2-m_v0).normalize();
        computeBBox();
    }

    Triangle::Triangle(Vec3f v0, Vec3f v1, Vec3f v2, Vec2f uv0, Vec2f uv1 ,Vec2f uv2, BlinnPhong* mat)
        : Triangle(v0, v1, v2, mat){
        m_uv0 = uv0;
        m_uv1 = uv1;
        m_uv2 = uv2;
    }

    Hit Triangle::intersect(Ray r) {
        Hit h;

        // We can write a point in a triangle ABC as
        // A + beta*A->B + gamma*A->C
        // We can write this out as 3 equations for x,y,z components and
        // do substitution and solve the system

        auto a = m_v0;
        auto b = m_v1;
        auto c = m_v2;

        Vec3f solution = cramers(
                Vec3f(a.x-b.x, a.y-b.y, a.z-b.z),
                Vec3f(a.x-c.x, a.y-c.y, a.z-c.z),
                Vec3f(r.d.x, r.d.y, r.d.z),
                Vec3f(a.x-r.o.x, a.y-r.o.y, a.z-r.o.z));

        float beta = solution[0];
        float gamma = solution[1];
        float t = solution[2];

        if (t > 0.001) {
            if ((beta >= 0) && (gamma >= 0) && ((beta + gamma) <= 1)) {
                h.hit = true;
                h.point = r.o + t*r.d;
                h.normal = normal.normalize();

                h.uvCoord = (m_uv0 + beta*(m_uv1 - m_uv0) + gamma*(m_uv2 - m_uv0));
            }
        }
        return h;
    }

    void Triangle::print() {
        std::cout << "Type = triangle" << std::endl;
        std::cout << "Point 1 = Vec3f(x=" << m_v0.x << ", y=" << m_v0.y << ", z=" << m_v0.z << ")" << std::endl;
        std::cout << "Point 2 = Vec3f(x=" << m_v1.x << ", y=" << m_v1.y << ", z=" << m_v1.z << ")" << std::endl;
        std::cout << "Point 3 = Vec3f(x=" << m_v2.x << ", y=" << m_v2.y << ", z=" << m_v2.z << ")" << std::endl;
    }


} //namespace rt
