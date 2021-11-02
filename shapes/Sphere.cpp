/*
 * Sphere.cpp
 *
 *
 */
#include "Sphere.h"
#include <cmath>


namespace rt{

    static double pow2(double x) {return x * x;}

	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */


	Hit Sphere::intersect(Ray ray){

//        std::cout << "testing intersection with sphere" << std::endl;


		Hit h;

        // So first we need to get the ray relative to our sphere
        // Sphere intersections are done with x^2+y^2+z^2=r^2 and it is assumed that the sphere is at the origin

        Ray objray = {.raytype=PRIMARY, .o=ray.o-(this->center), .d=ray.d-(this->center)};

        // If we sub our parametric ray into the sphere equation, we get some quadratic equation
        // at^2 + bt + c = 0
        // We need to solve for t here to basically get how far we need to move along our ray to get the
        // intersection point

        // Just using doubles here because why not?

        double a = pow2(objray.d.x) + pow2(objray.d.y) + pow2(objray.d.z);
        double b = 2 * ((objray.d.x * objray.o.x) + (objray.d.y * objray.o.y) + (objray.d.z * objray.o.z));
        double c = pow2(objray.o.x) + pow2(objray.o.y) + pow2(objray.o.z) - pow2(this->radius);

        // So we're going to solve the quadratic
        // We first use the discriminant to determine the number of roots
        // b^2 - 4ac

        double discriminant = pow2(b) - 4*a*c;

        // quadratic formula:
        // x = (-b +- sqrt(b^2 - 4ac)) / 2a

        if (discriminant >= 0) {  // Two distinct roots

//            std::cout << "Hit sphere!" << std::endl;

            double t1 = (-b + sqrt(discriminant)) / 2*a;
            double t2 = (b + sqrt(discriminant)) / 2*a;

            double t = (t1 < t2) ? t1 : t2;
            h.hit = true;
            h.point = objray.o + (float)t * objray.d;
        }

		return h;

	}

    void Sphere::print() {
        std::cout << "Type = Sphere" << std::endl;
        std::cout << "Centre = " << this->center << std::endl;
        std::cout << "Radius = " << this->radius << std::endl;
    }



} //namespace rt


