/*
 * Pinhole.cpp
 *
 *
 */
#include <iostream>

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

        // View plane is from -1,1, -1,1

        Vec3f bottomLeft(-1, -1, 1);
        float pixelWidth = 2/m_width;

        // This gets the bottom left corner of the pixel
        Vec3f xyPixel = bottomLeft + xPixel*Vec3f(pixelWidth, 0, 0) + yPixel*Vec3f(0, pixelWidth, 0);

        // This corrects to pixel centre
        xyPixel = xyPixel + Vec3f(pixelWidth/2, pixelWidth/2, 0);

        Vec3f rayDirection;

        cameraToWorld.multDirMatrix(xyPixel, rayDirection);

        Ray r = {.raytype = PRIMARY, .o = m_position, .d = rayDirection};

        return r;

    }


} //namespace rt

