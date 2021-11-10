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

        Vec3f topRight(-1, 1, dist);
        float pixelWidth = 2.0/m_width;

        // This gets the bottom left corner of the pixel
        Vec3f xyPixel = topRight + xPixel*Vec3f(pixelWidth, 0, 0) - yPixel*Vec3f(0, pixelWidth, 0);

        // This corrects to pixel centre
        xyPixel = xyPixel + Vec3f(pixelWidth/2, -pixelWidth/2, 0);


        if (yPixel == 0 && xPixel == 0) {
            std::cout << "(" << xPixel << "," << yPixel << ")" << std::endl;
            std::cout << "xyPixel = " << xyPixel << std::endl;
        }
        if (yPixel == 0 && xPixel == 799) {
            std::cout << "(" << xPixel << "," << yPixel << ")" << std::endl;

            std::cout << "xyPixel = " << xyPixel << std::endl;

        }
        if (yPixel == 799 && xPixel == 0) {
            std::cout << "(" << xPixel << "," << yPixel << ")" << std::endl;

            std::cout << "xyPixel = " << xyPixel << std::endl;

        }
        if (yPixel == 799 && xPixel == 799) {
            std::cout << "(" << xPixel << "," << yPixel << ")" << std::endl;

            std::cout << "xyPixel = " << xyPixel << std::endl;

        }
        

        Vec3f rayDirection;

        cameraToWorld.multDirMatrix(xyPixel, rayDirection);


        if (yPixel == 0 && xPixel == 0) {
            std::cout << "after transform = " << rayDirection << std::endl;
        }
        if (yPixel == 0 && xPixel == 799) {
            std::cout << "after transform = " << rayDirection << std::endl;
        }
        if (yPixel == 799 && xPixel == 0) {
            std::cout << "after transform = " << rayDirection << std::endl;
        }
        if (yPixel == 799 && xPixel == 799) {
            std::cout << "after transform = " << rayDirection << std::endl;
        }

        Ray r = {.raytype = PRIMARY, .o = m_position, .d = rayDirection.normalize()};

        return r;

    }


} //namespace rt

