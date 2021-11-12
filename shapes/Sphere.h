/*
 * Sphere.h
 *
 *
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "math/geometry.h"
#include "core/RayHitStructs.h"
#include "core/Shape.h"
#include "materials/BlinnPhong.h"

namespace rt{

class Sphere:public Shape{

public:

	//
	// Constructors
	//
	Sphere(Vec3f center, float radius, BlinnPhong* mat);

	~Sphere() override  {
        std::cout << "Destroyed sphere!" << std::endl;
    };


	Hit intersect(Ray ray) override;

    void print();

private:

	Vec3f center;
	float radius;

};



} //namespace rt




#endif /* SPHERE_H_ */
