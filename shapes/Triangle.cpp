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

    Hit Triangle::intersect(Ray r) {
        Hit h;

        // Going to redo this

        // normal
//        Vec3f normal = (m_v1-m_v0).crossProduct(m_v2-m_v1);

//         This will break if the direction vector is perpendicular to the normal
//        float s = ((m_v0 - r.o).dotProduct(normal)) / r.d.dotProduct(normal);

//        if (s <= 0) {
//            return h;
//        }

        // Now we have the intersection point
//        Vec3f intersect = ray.o + s*ray.d;

//        std::cout << intersect << std::endl;

        // Going to swap this code for the barycentric stuff I calculated and from that video
        // https://www.youtube.com/watch?v=HYAgJN3x4GA
        // https://www.youtube.com/watch?v=B8Q1nqW3XcE

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

//                h.uvCoord = Vec2f(beta*material.getTWidth(), gamma*material.getTHeight());
            }
        }

        // using cramers rule


//        float beta =

//        float beta = (A.x*(C.y - A.y) + (P.y - A.y)*(C.x - A.x) - P.x*(C.y - A.y)) / ((B.y - A.y)*(C.x - A.x) - (B.x - A.x)*(C.y - A.y));
//        float gamma = (P.y - A.y - beta*(B.y - A.y)) / (C.y - A.y);

//
//        float beta = (m_v0.x*(m_v2.y-m_v0.y) + (intersect.y-m_v0.y)*(m_v2.x-m_v0.x) - intersect.x*(m_v2.y-m_v0.y)) / ((m_v1.y-m_v0.y)*(m_v2.x-m_v0.x) - (m_v1.x-m_v0.x)*(m_v2.y-m_v0.y));
//        float gamma = (intersect.y - m_v0.y - beta*(m_v1.y-m_v0.y)) / (m_v2.y-m_v0.y);


//        Vec3f v0tov1 = m_v1 - m_v0;
//        Vec3f v0toI = intersect - m_v0;
//        Vec3f crs1 = v0tov1.crossProduct(v0toI);
//
//        Vec3f v1tov2 = m_v2 - m_v1;
//        Vec3f v1toI = intersect - m_v1;
//        Vec3f crs2 = v1tov2.crossProduct(v1toI);
//
//        Vec3f v2tov0 = m_v0 - m_v2;
//        Vec3f v2toI = intersect - m_v2;
//        Vec3f crs3 = v2tov0.crossProduct(v2toI);
//
//        float dot1 = crs1.dotProduct(normal);
//        float dot2 = crs2.dotProduct(normal);
//        float dot3 = crs3.dotProduct(normal);
//
//        if (dot1>0 && dot2>0 && dot3>0) {
//            h.hit = true;
//            h.point = intersect;
//            h.normal = normal;
////            std::cout << "HIT" << std::endl;
//        }

//         Intersection!

//        std::cout << "beta=" << beta << " gamma=" << gamma << std::endl;
//        if ((beta >= 0) && (gamma >= 0) && ((beta+gamma) <= 1)) {
//        if (((beta+gamma) <= 1)) {
//        if (true) {
//            h.hit = true;
//            h.point = intersect;
//            h.normal = normal;
//        }


        return h;
    }

    void Triangle::print() {
        std::cout << "Type = triangle" << std::endl;
        std::cout << "Point 1 = Vec3f(x=" << m_v0.x << ", y=" << m_v0.y << ", z=" << m_v0.z << ")" << std::endl;
        std::cout << "Point 2 = Vec3f(x=" << m_v1.x << ", y=" << m_v1.y << ", z=" << m_v1.z << ")" << std::endl;
        std::cout << "Point 3 = Vec3f(x=" << m_v2.x << ", y=" << m_v2.y << ", z=" << m_v2.z << ")" << std::endl;
    }


} //namespace rt
