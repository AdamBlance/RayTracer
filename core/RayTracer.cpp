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

            float minDist = 1000000;
            Shape* intersectingShape;
            Hit hit;

            // Get closest intersection
            for (auto& shape : scene->getShapes()) {
                Hit shapeHit = shape->intersect(r);
                if (shapeHit.hit) {
                    float dist = (shapeHit.point - r.o).length();
                    if (dist < minDist) {
                        minDist = dist;
                        hit = shapeHit;
                        intersectingShape = shape;
                    }
                }
            }

            if (hit.hit) {

                BlinnPhong mat = intersectingShape->getMaterial();

                float ia = 0.1;
                Vec3f pointColour = ia * mat.getDiffusecolor();

                for (auto& light : scene->getLightSources()) {

                    float dist = (light->getPosition() - hit.point).length();
//                        std::cout << dist << std::endl;

                    Vec3f L = (light->getPosition() - hit.point).normalize();
                    float LdotN = std::max<float>(0, L.dotProduct(hit.normal));
//                        Vec3f diffuse = mat.getKd()*mat.getDiffusecolor() * LdotN * light->getDiffuseIntensity() * (1 / (dist*dist));
                    Vec3f diffuse = mat.getKd()*mat.getDiffusecolor() * LdotN * light->getDiffuseIntensity();

                    Vec3f V = (-1*r.d).normalize();
                    Vec3f H = (L+V) * (1/(L+V).length());
                    float NdotH = std::max<float>(0, H.dotProduct(hit.normal));


//                        Vec3f specular = mat.getKs() * powf(NdotH, (float)mat.getSpecularexponent()) * light->getSpecularIntensity() * (1 / (dist*dist));
                    Vec3f specular = mat.getKs() * powf(NdotH, (float)mat.getSpecularexponent()) * light->getSpecularIntensity();

                    pointColour = pointColour + (diffuse + specular);
//                        float kd = mat.getKd();
//                        float ks = mat.getKs();
//                        float alpha = mat.getSpecularexponent();
//
//                        Vec3f L = (light->getPosition() - hit.point).normalize();
//                        Vec3f N = hit.normal;
//                        float id = light->getDiffuseIntensity().x;
//                        float is = light->getSpecularIntensity().x;
//
//
//                        I_p += kd*(std::max<float>(0.0, L.dotProduct(N)))*id + powf(ks*(std::max<float>(0.0, N.dotProduct(H))), alpha)*is;



                }
                pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = pointColour;

//                    std::cout << "colour = " << colour << std::endl;

//                    std::cout << "before normal " << hit.normal << std::endl;
//                    hit.normal = hit.normal.normalize();
//                    std::cout << "after normal " << hit.normal << std::endl;
//                    pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = 0.5*Vec3f(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1)*255;
            }

        }
    }

	return pixelbuffer;

}
 // https://paroj.github.io/gltut/Illumination/Tutorial%2012.html
/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer){

	//---------tonemapping function to be filled--------

    float max = 0;

    for (int i = 0; i < 800*800; i++) {
        Vec3f pixel = *(pixelbuffer+i);

        float maxOfCurrent = std::max<float>(pixel.x, std::max<float>(pixel.y, pixel.z));
        if (maxOfCurrent > max) {
            max = maxOfCurrent;
        }
    }

    std::cout << max << std::endl;

    for (int i = 0; i < 800*800; i++) {
        *(pixelbuffer+i) *= (255/max);
    }

	return pixelbuffer;

}




} //namespace rt


