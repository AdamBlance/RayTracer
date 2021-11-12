/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <materials/BlinnPhong.h>
#include "core/Material.h"
#include "rapidjson/document.h"
#include "core/RayHitStructs.h"
#include "BoundingStruct.h"


namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape() = default;
    explicit Shape(BlinnPhong mat) : material{mat} {};


    static Shape* createShape(rapidjson::Value& shapeSpecs);


    //
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape();

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray)=0;

//    virtual BoundingBox getBBox();

    BlinnPhong getMaterial() {
        return material;
    }

protected:

	BlinnPhong material;

};


} //namespace rt


#endif /* SHAPE_H_ */
