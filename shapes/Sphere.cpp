/*
 * Sphere.cpp
 *
 *
 */
#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <cmath>


namespace rt{

    static float pow2(float x) {return x * x;}

	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */


	Hit Sphere::intersect(Ray ray){



		Hit h;

        // So first we need to get the ray relative to our sphere
        // Sphere intersections are done with x^2+y^2+z^2=r^2 and it is assumed that the sphere is at the origin

        Ray objray = {.raytype=PRIMARY, .o=ray.o-(this->center), .d=ray.d};

        // If we sub our parametric ray into the sphere equation, we get some quadratic equation
        // at^2 + bt + c = 0
        // We need to solve for t here to basically get how far we need to move along our ray to get the
        // intersection point

        // Just using doubles here because why not?

        float a = pow2(objray.d.x) + pow2(objray.d.y) + pow2(objray.d.z);
        float b = 2 * ((objray.d.x * objray.o.x) + (objray.d.y * objray.o.y) + (objray.d.z * objray.o.z));
        float c = pow2(objray.o.x) + pow2(objray.o.y) + pow2(objray.o.z) - pow2(this->radius);

        // So we're going to solve the quadratic
        // We first use the discriminant to determine the number of roots
        // b^2 - 4ac

        float discriminant = pow2(b) - 4*a*c;

        // quadratic formula:
        // x = (-b +- sqrt(b^2 - 4ac)) / 2a

        if (discriminant >= 0) {  // Two distinct roots

//            std::cout << "Hit sphere!" << std::endl;

            float t1 = (-b + sqrtf(discriminant)) / (2*a);
            float t2 = (-b - sqrtf(discriminant)) / (2*a);

            float t;

            if (t1 < 0.001 && t2 < 0.001) {
                return h;
            } else if (std::min(t1, t2) < 0.001) {
                t = std::max(t1, t2);
            } else {
                t = (t1 < t2) ? t1 : t2;
            }

            h.hit = true;
            h.point = ray.o + t*ray.d;
            // Since the sphere is centred at origin, the point of intersection should be the normal

            h.normal = (objray.o + t*objray.d).normalize();

            if (material.getTPath() != "none") {

                Vec3f rel = objray.o + t*objray.d;

                float phi = atan2f(rel.y, rel.x);
                float theta = acosf(rel.z/radius);

//                std::cout << phi << " " << theta << std::endl;

                // phi is x coord
                // in range of -pi to pi

                h.uvCoord.x = ((phi+M_PI)/(2*M_PI));
                h.uvCoord.y = (theta/M_PI);

//                std::cout << h.uvCoord << std::endl;



            }



        }

		return h;

	}

    void Sphere::print() {
        std::cout << "Type = Sphere" << std::endl;
        std::cout << "Centre = " << this->center << std::endl;
        std::cout << "Radius = " << this->radius << std::endl;
    }



} //namespace rt


