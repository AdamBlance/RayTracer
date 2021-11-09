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
        shapes.push_back(Shape::createShape(shape));
        }
    }







} //namespace rt



