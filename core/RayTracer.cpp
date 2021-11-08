/*
 * RayTracer.cpp
 *
 */
#define _USE_MATH_DEFINES
#include "RayTracer.h"
#include <cmath>

namespace rt{


/**
 * Performs ray tracing to render a photorealistic scene
 *
 * @param camera the camera viewing the scene
 * @param scene the scene to render, including objects and lightsources
 * @param nbounces the number of bounces to consider for raytracing
 *
 * @return a pixel buffer containing pixel values in linear RGB format
 */
Vec3f* RayTracer::render(Camera* camera, Scene* scene, int nbounces){

	Vec3f* pixelbuffer=new Vec3f[camera->getWidth()*camera->getHeight()];

    for (int y_pixel = 0; y_pixel < camera->getHeight(); y_pixel++) {
        for (int x_pixel = 0; x_pixel < camera->getWidth(); x_pixel++) {

//            pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = scene->getBackgroundColour();
            pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = Vec3f(0, 0, 0);

            Ray r = camera->castRay(x_pixel, y_pixel);

            Vec3f p = r.o + r.d;
            if (y_pixel == 0 && x_pixel == 0) {
                std::cout << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
            }
            if (y_pixel == 0 && x_pixel == 799) {
                std::cout << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
            }
            if (y_pixel == 799 && x_pixel == 0) {
                std::cout << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
            }
            if (y_pixel == 799 && x_pixel == 799) {
                std::cout << "(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
            }




            for (auto& shape : scene->getShapes()) {
                if (shape->intersect(r).hit) {
                    pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = Vec3f(255, 255, 255);
                    break;
                }
            }

            if (y_pixel == 700 && x_pixel == 700) {
                pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = Vec3f(255, 0, 255);
            }
        }
    }

	return pixelbuffer;

}

/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------

	return pixelbuffer;

}





} //namespace rt


