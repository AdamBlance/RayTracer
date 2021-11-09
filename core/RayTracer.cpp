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

            pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = scene->getBackgroundColour()*255;

            Ray r = camera->castRay(x_pixel, y_pixel);

            for (auto& shape : scene->getShapes()) {
                Hit hit = shape->intersect(r);
                if (hit.hit) {

                    BlinnPhong mat = shape->getMaterial();

                    float I_p = mat.;
                    for (auto& light : scene->getLightSources()) {

                        float kd = mat.getKd();
                        float ks = mat.getKs();
                        float alpha = mat.getSpecularexponent();

                        Vec3f L = (light->getPosition() - hit.point).normalize();
                        Vec3f N = hit.normal;
                        Vec3f V = (-1*r.d).normalize();
                        float id = light->getDiffuseIntensity().x;
                        float is = light->getSpecularIntensity().x;

                        Vec3f H = (L+V) * (1/(L+V).length());

                        I_p += kd*(std::max<float>(0.0, L.dotProduct(N)))*id + powf(ks*(std::max<float>(0.0, N.dotProduct(H))), alpha)*is;


                    }

                    Vec3f colour = shape->getMaterial().getDiffusecolor()*I_p;

//                    std::cout << "colour = " << colour << std::endl;

                    pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = colour;
                    break;
                }
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


