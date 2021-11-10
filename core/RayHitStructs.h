/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"


namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{

	RayType raytype = PRIMARY;

	//----------Ray variables to be filled------

    // This was "origin" and "direction" but it started getting really cumbersome
    Vec3f o; // origin
    Vec3f d; // direction

};


struct Hit{

	Vec3f point; //point where ray hits a shape
    bool hit = false;
    Vec3f normal;

};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
