/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{

    Hit Triangle::intersect(Ray ray) {
        Hit h;

        // REMEMBER
        // V0 -> V1 == V1-V0, NOT THE OTHER WAY

        // normal
        Vec3f normal = (m_v1-m_v0).crossProduct(m_v2-m_v1);

        // This will break if the direction vector is perpendicular to the normal
        float s = ((m_v0 - ray.o).dotProduct(normal)) / ray.d.dotProduct(normal);

        if (s <= 0) {
//            std::cout << "negative" << std::endl;
            return h;
        }

//        std::cout << "positive!" << std::endl;

//        std::cout << ray. << std::endl;

//        std::cout << ray.o;
//        std::cout << ray.d;

        // Now we have the intersection point
        Vec3f intersect = ray.o + s*ray.d;



//        std::cout << intersect;


        // We need to check whether the intersection point is inside the triangle
        // Just like the drone project thing, go around the edges of the triangle testing the dot product

        // Okay, just like the drone thing I got confused.
        // DOT product is positive when vector angles are acute
        // 0 when perpendicular
        // Negative when obtuse


//        float v0tov1dot = (m_v0 - m_v1).dotProduct(m_v0 - intersect);
//        float v1tov2dot = (m_v1 - m_v2).dotProduct(m_v1 - intersect);
//        float v2tov0dot = (m_v2 - m_v0).dotProduct(m_v2 - intersect);

        Vec3f v0tov1 = m_v1 - m_v0;
        Vec3f v0toI = intersect - m_v0;
        Vec3f crs1 = v0tov1.crossProduct(v0toI);

        Vec3f v1tov2 = m_v2 - m_v1;
        Vec3f v1toI = intersect - m_v1;
        Vec3f crs2 = v1tov2.crossProduct(v1toI);

        Vec3f v2tov0 = m_v0 - m_v2;
        Vec3f v2toI = intersect - m_v2;
        Vec3f crs3 = v2tov0.crossProduct(v2toI);



        float dot1 = crs1.dotProduct(normal);
        float dot2 = crs2.dotProduct(normal);
        float dot3 = crs3.dotProduct(normal);

//        std::cout << (dot1>0 ? " P" : " N");
//        std::cout << (dot2>0 ? "P" : "N");
//        std::cout << (dot3>0 ? "P" : "N") << std::endl;

//        std::cout << crs1;
//        std::cout << crs2;
//        std::cout << crs3 << std::endl;

//        std::cout << dot1 << " " << dot2 << " " << dot3 << std::endl;

        if (dot1>0 && dot2>0 && dot3>0) {
            h.hit = true;
            h.point = intersect;
//            std::cout << "HIT" << std::endl;
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
