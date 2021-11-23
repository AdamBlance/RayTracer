/*
 * Pinhole.cpp
 *
 *
 */
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Pinhole.h"



namespace rt{

	//
	// Pinhole constructor (example)
	//
	Pinhole::Pinhole(int width, int height, int fov, Vec3f position, Vec3f lookat, Vec3f up):Camera(width, height, fov, position, lookat, up){
	}


	/**
	 * Prints camera data
	 * this function implements the abstract function of the base Camera class
	 */
	void Pinhole::printCamera(){
		printf("I am a pinhole camera! \n");
		printf("width: %dpx, height: %dpx, fov:%d \n", m_width, m_height, m_fov);
	}

    // Returns a ray in world space
    Ray Pinhole::castRay(int xPixel, int yPixel) {

        // FOV determines distance of view plane from camera origin
        float dist = tanf((90 - 0.5*m_fov) * (M_PI/180));

        // View plane is from -1,1, -1,1
        // Camera points in the -z direction, easier to imagine than +z (I think anyway)
        Vec3f topLeft(-1, 1, -dist);
        float pixelWidth = 2.0/m_width;

        // This gets the top left corner of the pixel (no it doesn't?)
        Vec3f xyPixel = topLeft + xPixel*Vec3f(pixelWidth, 0, 0) - yPixel*Vec3f(0, pixelWidth, 0);

        // This corrects to pixel centre
        xyPixel = xyPixel + Vec3f(pixelWidth/2, -pixelWidth/2, 0);

//        std::cout << "Camera ray -> " << xyPixel << std::endl;

        xyPixel = xyPixel.normalize();

        Vec3f rayDirection;

//        cameraToWorld.multDirMatrix(xyPixel, rayDirection);

        rayDirection.x = cameraToWorld[0][0]*xyPixel.x + cameraToWorld[0][1]*xyPixel.y + cameraToWorld[0][2]*xyPixel.z;
        rayDirection.y = cameraToWorld[1][0]*xyPixel.x + cameraToWorld[1][1]*xyPixel.y + cameraToWorld[1][2]*xyPixel.z;
        rayDirection.z = cameraToWorld[2][0]*xyPixel.x + cameraToWorld[2][1]*xyPixel.y + cameraToWorld[2][2]*xyPixel.z;


        Ray r = {.raytype = PRIMARY, .o = m_position, .d = rayDirection.normalize()};

//        std::cout << "Ray direction -> " << rayDirection << std::endl;


        return r;

    }


} //namespace rt

