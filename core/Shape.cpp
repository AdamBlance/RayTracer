/*
 * Shape.cpp
 *
 */
#include <shapes/TriMesh.h>
#include <shapes/Plane.h>
#include "Shape.h"
#include "utility/Helper.h"
#include "shapes/Sphere.h"
#include "shapes/Triangle.h"


namespace rt{


    Shape::~Shape() {

    }

    Shape* Shape::createShape(rapidjson::Value& shapeSpecs) {

        if (!shapeSpecs.HasMember("type")){
            std::cerr<<"Shape type not specified"<<std::endl;
            exit(-1);
        }

        std::string shapeType = shapeSpecs["type"].GetString();

        if (shapeType == "sphere") {
            Vec3f center = Helper::toVec3f(shapeSpecs["center"].GetArray());
            float radius = shapeSpecs["radius"].GetFloat();
            return new Sphere(center, radius);
        } else if (shapeType == "triangle") {
            Vec3f v0 = Helper::toVec3f(shapeSpecs["v0"].GetArray());
            Vec3f v1 = Helper::toVec3f(shapeSpecs["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shapeSpecs["v2"].GetArray());
            return new Triangle(v0, v1, v2);
        } else if (shapeType == "plane") {
            Vec3f v1 = Helper::toVec3f(shapeSpecs["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shapeSpecs["v2"].GetArray());
            Vec3f v3 = Helper::toVec3f(shapeSpecs["v3"].GetArray());
            Vec3f v0 = Helper::toVec3f(shapeSpecs["v0"].GetArray());
            return new Plane(v1, v2, v3, v0);
        } else {
            return nullptr;
        }


    }

} //namespace rt

