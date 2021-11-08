/*
 * Camera.cpp
 *
 */
#include <iostream>

#include "Camera.h"
#include "cameras/Pinhole.h"
#include "cameras/ThinLens.h"
#include "Scene.h"
#include "utility/Helper.h"

namespace rt{

    // I know I should use initialiser lists but I don't like them
    Camera::Camera(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up) {
        m_width = width;
        m_height = height;
        m_fov = fov;
        m_position = position;
        m_lookat = lookat;
        m_up = up;

        // Camera i-hat basis vector can be computed by crossing up and lookat
        Vec3f iHat = m_lookat.crossProduct(m_up).normalize();
        // Camera j-hat basis vector can be computed by crossing iHat with lookat
        Vec3f jHat = iHat.crossProduct(m_lookat).normalize();

        cameraToWorld[0][0] = iHat[0];
        cameraToWorld[1][0] = iHat[1];
        cameraToWorld[2][0] = iHat[2];
        cameraToWorld[3][0] = 0.0;

        cameraToWorld[0][1] = jHat[0];
        cameraToWorld[1][1] = jHat[1];
        cameraToWorld[2][1] = jHat[2];
        cameraToWorld[3][1] = 0.0;

        cameraToWorld[0][2] = m_lookat[0];
        cameraToWorld[1][2] = m_lookat[1];
        cameraToWorld[2][2] = m_lookat[2];
        cameraToWorld[3][2] = 0.0;

        cameraToWorld[0][3] = m_position[0];
        cameraToWorld[1][3] = m_position[1];
        cameraToWorld[2][3] = m_position[2];
        cameraToWorld[3][3] = 1.0;

    }

	Camera::~Camera(){};



/**
 * Factory function that returns camera subclass based on camera specifications
 *
 * @param cameraSpecs camera specifications json object
 *
 * @return camera subclass instance
 *
 */
Camera* Camera::createCamera(Value& cameraSpecs){

	//check if cameratype is defined
	if (!cameraSpecs.HasMember("type")){
		std::cerr<<"Camera type not specified"<<std::endl;
		exit(-1);
	}

	std::string cameraType = cameraSpecs["type"].GetString();

    int cameraHeight = cameraSpecs["width"].GetInt();
    int cameraWidth = cameraSpecs["height"].GetInt();
    int cameraFov = cameraSpecs["fov"].GetInt();
    Vec3f cameraPosition = Helper::toVec3f(cameraSpecs["position"].GetArray());
    Vec3f cameraLookat = Helper::toVec3f(cameraSpecs["lookat"].GetArray());
    Vec3f cameraUp = Helper::toVec3f(cameraSpecs["up"].GetArray());

    if (cameraType == "pinhole") {
        return new Pinhole(cameraWidth, cameraHeight, cameraFov, cameraPosition, cameraLookat, cameraUp);
    } else if (cameraType == "thinlens") {
        return new ThinLens(cameraWidth, cameraHeight, cameraFov, cameraPosition, cameraLookat, cameraUp);
    } else {
        std::cerr<<"Invalid camera type"<<std::endl;
        exit(-1);
    }

}



} //namespace rt
