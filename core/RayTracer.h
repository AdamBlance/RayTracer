/*
 * RayTracer.h
 *
 */
#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "math/geometry.h"
#include "core/Camera.h"
#include "core/Scene.h"

namespace rt{



/*
 * Raytracer class declaration
 */
class RayTracer {
public:

	RayTracer();

	static Vec3f* render(Camera* camera, Scene* scene, int nbounces);
	static Vec3f* tonemap(Vec3f* pixelbuffer, int length);
    static Vec3f colourAtHit(Ray ray, Scene* scene, int nbounces);
    static bool pointInShade(Vec3f point, Scene* scene, LightSource* light);


};




} //namespace rt



#endif /* RAYTRACER_H_ */

