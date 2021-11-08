/*
 * Shape.h
 *
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "core/RayHitStructs.h"
#include "core/Material.h"
#include "rapidjson/document.h"


namespace rt{

class Shape{
public:

	//
	// Constructors
	//
	Shape() : id{"empty"} {}

    static Shape* createShape(rapidjson::Value& shapeSpecs);


    //
	// Destructor (must be overriden in subclass)
	//
	virtual ~Shape();

	//
	// Shape abstract methods (to be implemented by subclasses)
	//
	virtual Hit intersect(Ray)=0;


protected:

    std::string id;
//	Material * material;

};


} //namespace rt


#endif /* SHAPE_H_ */
