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

	//----------main rendering function to be filled------

    // Okay so viewport will be 2x2
    // -1, 1
    // -1, 1

    // We need a vector that is perpendicular to both the lookat and the up vector.
    // This lets us point left and right on the viewport
    Vec3f camera_x = camera->getLookat().crossProduct(camera->getUp()).normalize();

    // Then we should have a perpendicular vector pointing right I think
    // So we have the lookat and this right pointing vector, so the cross product of
    // ...the right vector and the lookat should give us the camera_y vector

    Vec3f camera_y = camera_x.crossProduct(camera->getLookat()).normalize();


    // We should calculate the centre of the top left pixel
    // Then we can just add one pixel's worth to get the rest

    float dist = tanf((90 - 0.5*camera->getFov()) * (M_PI/180) );
//
//    dist *= 0.001;

//    std::cout << dist << std::endl;

    Vec3f point_to_top_left = camera->getPosition() + camera->getLookat().normalize()*dist - camera_x  + camera_y + camera_x*(1.0/camera->getWidth()) - camera_y*(1.0/camera->getHeight());
//    Vec3f point_to_top_left = camera->getPosition() + camera->getLookat().normalize()*tanf((M_PI - camera->getFov()*(M_PI/180))/2) - camera_x + camera_x*(1.0/camera->getWidth());

    std::cout << point_to_top_left << std::endl;

    for (int y_pixel = 0; y_pixel < camera->getHeight(); y_pixel++) {
        for (int x_pixel = 0; x_pixel < camera->getWidth(); x_pixel++) {


            // Okay so we need to cast one ray for each pixel in the image.
            // We create a ray with the origin of the camera
            // The camera's lookat vector points to the very centre of the viewport.

            Vec3f point_at_pixel = point_to_top_left + x_pixel*camera_x*(1.0/(0.5*camera->getWidth())) - y_pixel*camera_y*(1.0/(0.5*camera->getHeight()));
//            Vec3f point_at_pixel = point_to_top_left + x_pixel*camera_x*(1.0/(0.5*camera->getWidth()));

//            std::cout << "(" << x_pixel << "," << y_pixel << ") ";

            if (y_pixel == 0 && x_pixel == 799){
                std::cout << point_at_pixel << std::endl;
            } else if (y_pixel == 799 && x_pixel == 0) {
                std::cout << point_at_pixel << std::endl;
            } else if (y_pixel == 799 && x_pixel==799) {
                std::cout << point_at_pixel << std::endl;
            }

//            std::cout << acos( ((camera->getLookat().normalize()*tanf((M_PI - camera->getFov()*(M_PI/180))/2)).dotProduct(point_at_pixel)) / ((camera->getLookat().normalize()*tanf((M_PI - camera->getFov()*(M_PI/180))/2)).length()*point_at_pixel.length()) ) * (180.0/3.141592653589793238463) << std::endl;

//            Ray ray = {.raytype=PRIMARY, .o=camera->getPosition(), .d=(point_at_pixel-camera->getPosition()).normalize()};
            Ray ray = {.raytype=PRIMARY, .o=camera->getPosition(), .d=(point_at_pixel).normalize()};

//            std::cout << (y_pixel*camera->getHeight()) + x_pixel << std::endl;

            pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = Vec3f(0, 0, 0);




            for (auto& shape : scene->getShapes()) {
                if (shape->intersect(ray).hit) {
                    pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = Vec3f(255, 255, 255);
                    break;
                }
            }
        }
    }

//
//        for ( int i = 0; i < 200; i++)
//            std::cout << *(pixelbuffer + i) << ", ";



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


