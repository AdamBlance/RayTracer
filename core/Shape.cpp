/*
 * Shape.cpp
 *
 */
#include <shapes/TriMesh.h>
#include <shapes/Plane.h>
#include <materials/BlinnPhong.h>
#include <shapes/BVH.h>
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

        BlinnPhong* mat;
        if (shapeSpecs.HasMember("material")) {
            float ks = shapeSpecs["material"]["ks"].GetFloat();
            float kd = shapeSpecs["material"]["kd"].GetFloat();
            int specularexponent = shapeSpecs["material"]["specularexponent"].GetInt();
            Vec3f diffusecolor = Helper::toVec3f(shapeSpecs["material"]["diffusecolor"].GetArray());

            float kr = shapeSpecs["material"].HasMember("kr") ? shapeSpecs["material"]["kr"].GetFloat() : 0.0f;

            if (shapeSpecs["material"].HasMember("tPath")) {
                std::string tPath = shapeSpecs["material"]["tPath"].GetString();
                int tWidth = shapeSpecs["material"]["tWidth"].GetInt();
                int tHeight = shapeSpecs["material"]["tHeight"].GetInt();
                mat = new BlinnPhong(ks, kd, kr, specularexponent, diffusecolor, tPath, tWidth, tHeight);
            } else {
                mat = new BlinnPhong(ks, kd, kr, specularexponent, diffusecolor);
            }
        }

        if (shapeType == "sphere") {
            Vec3f center = Helper::toVec3f(shapeSpecs["center"].GetArray());
            float radius = shapeSpecs["radius"].GetFloat();
            return new Sphere(center, radius, mat);
        } else if (shapeType == "triangle") {
            Vec3f v0 = Helper::toVec3f(shapeSpecs["v0"].GetArray());
            Vec3f v1 = Helper::toVec3f(shapeSpecs["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shapeSpecs["v2"].GetArray());
            return new Triangle(v0, v1, v2, mat);
        } else if (shapeType == "plane") {
            Vec3f v1 = Helper::toVec3f(shapeSpecs["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shapeSpecs["v2"].GetArray());
            Vec3f v3 = Helper::toVec3f(shapeSpecs["v3"].GetArray());
            Vec3f v0 = Helper::toVec3f(shapeSpecs["v0"].GetArray());
            return new Plane(v1, v2, v3, v0, mat);
        } else if (shapeType == "trimesh") {
            std::string filename = shapeSpecs["mPath"].GetString();
//            TriMesh* mesh = new TriMesh(filename, mat);
            auto* triList = PLYReader::PLYReader(filename);
            return new BVH(triList, 0, (int) triList->size(), mat);
        } else {
            return nullptr;
        }


    }

} //namespace rt

