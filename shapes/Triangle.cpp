/*
 * Triangle.cpp
 *
 *
 */
#include "Triangle.h"



namespace rt{



    Hit Triangle::intersect(Ray ray) {
        Hit h;

        // normal
        Vec3f normal = (m_v0-m_v1).crossProduct(m_v1-m_v2);


        // This will break if the direction vector is perpendicular to the normal
        float s = ((m_v0 - ray.o).dotProduct(normal)) / ray.d.dotProduct(normal);

        // Now we have the intersection point
        Vec3f intersect = ray.o + s*ray.d;

        // We need to check whether the intersection point is inside the triangle
        // Just like the drone project thing, go around the edges of the triangle testing the dot product

        // Okay, just like the drone thing I got confused.
        
        float v0tov1dot = (m_v0 - m_v1).dotProduct(m_v0 - intersect);
        float v1tov2dot = (m_v1 - m_v2).dotProduct(m_v1 - intersect);
        float v2tov0dot = (m_v2 - m_v0).dotProduct(m_v2 - intersect);

        if (v0tov1dot>=0 && v1tov2dot>=0 && v2tov0dot>=0) {
            h.hit = true;
            h.point = intersect;
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
