/*
 * Scene.cpp
 *
 */
#include <shapes/TriMesh.h>
#include <Helper.h>
#include "Scene.h"
#include "lights/PointLight.h"
#include "lights/AreaLight.h"
#include "shapes/Sphere.h"


namespace rt{

/**
 * Parses json scene object to generate scene to render
 *
 * @param scenespecs the json scene specificatioon
 */
void Scene::createScene(Value& scenespecs){

	//----------parse json object to populate scene-----------

    backgroundColour = Helper::toVec3f(scenespecs["backgroundcolor"].GetArray());

    // For each JSON lightsource
    for (auto& lightsource : scenespecs["lightsources"].GetArray()) {

        // Extract type, specular intensity, diffuse intensity
        std::string light_type = lightsource["type"].GetString();
        Vec3f position = Helper::toVec3f(lightsource["position"].GetArray());
        Vec3f specular_intensity = Helper::toVec3f(lightsource["is"].GetArray());
        Vec3f diffuse_intensity = Helper::toVec3f(lightsource["id"].GetArray());

        if (light_type == "pointlight") {
            lightSources.push_back(new PointLight(position, specular_intensity, diffuse_intensity));
        } else if (light_type == "arealight") {
            lightSources.push_back(new AreaLight(position, specular_intensity, diffuse_intensity));
        }

    }

    // For each JSON shape
    for (auto& shape : scenespecs["shapes"].GetArray()) {

        std::string shape_type = shape["type"].GetString();

        if (shape_type == "sphere") {
            Vec3f center = Helper::toVec3f(shape["center"].GetArray());
            float radius = shape["radius"].GetFloat();
            shapes.push_back(new Sphere(center, radius));
        } else if (shape_type == "plane") {

            Vec3f v1 = Helper::toVec3f(shape["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shape["v2"].GetArray());
            Vec3f v3 = Helper::toVec3f(shape["v3"].GetArray());
            Vec3f v0 = Helper::toVec3f(shape["v0"].GetArray());

            shapes.push_back(new Triangle(v1, v2, v3));
            shapes.push_back(new Triangle(v3, v0, v1));
        } else if (shape_type == "triangle") {
            Vec3f v0 = Helper::toVec3f(shape["v0"].GetArray());
            Vec3f v1 = Helper::toVec3f(shape["v1"].GetArray());
            Vec3f v2 = Helper::toVec3f(shape["v2"].GetArray());

            shapes.push_back(new Triangle(v0, v1, v2));
        }
    }



}





} //namespace rt



