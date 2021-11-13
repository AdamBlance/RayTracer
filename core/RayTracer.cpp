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
        if (y_pixel % 10 == 0) std::cout << "ln " << y_pixel << std::endl;
        for (int x_pixel = 0; x_pixel < camera->getWidth(); x_pixel++) {

            Ray r = camera->castRay(x_pixel, y_pixel);

            pixelbuffer[(y_pixel*camera->getHeight()) + x_pixel] = colourAtHit(r, scene, nbounces);

        }
    }

	return pixelbuffer;

}
bool RayTracer::pointInShade(Vec3f point, Scene* scene, LightSource* light) {
    for (auto& shape : scene->getShapes()) {
        Ray rayToLight = {.raytype=SHADOW, .o=point, .d=(light->getPosition()-point)};
        if (shape->intersect(rayToLight).hit) {
            return true;
        }
    }
    return false;
}

Vec3f RayTracer::colourAtHit(Ray r, Scene* scene, int nbounces) {

    if (nbounces == 0) {
        return {};
    }

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
        BlinnPhong* mat = intersectingShape->getMaterial();

        Vec3f diffColour;
        if (mat->getTPath() == "none") {
            diffColour = mat->getDiffusecolor();
        } else {

            int x = (int) (hit.uvCoord.x * (float) mat->getTWidth());
            int y = (int) (hit.uvCoord.y * (float) mat->getTHeight());

            diffColour = mat->getTexture()[y*mat->getTWidth() + x];
        }

        float ia = 0.02; // ambient intensity
        Vec3f pointColour = ia * diffColour;

        for (auto& light : scene->getLightSources()) {

            if (pointInShade(hit.point, scene, light)) {
                continue;
            }

            float dist = (light->getPosition() - hit.point).length();
            Vec3f L = (light->getPosition() - hit.point).normalize();
            float LdotN = std::max<float>(0, L.dotProduct(hit.normal));
            Vec3f diffuse = mat->getKd()*diffColour * LdotN * light->getDiffuseIntensity() * (1 / (dist*dist));
            Vec3f V = (-1*r.d).normalize();
            Vec3f H = (L+V) * (1/(L+V).length());
            float NdotH = std::max<float>(0, H.dotProduct(hit.normal));
            Vec3f specular = mat->getKs() * powf(NdotH, (float)mat->getSpecularexponent()) * light->getSpecularIntensity() * (1 / (dist*dist));

            pointColour = pointColour + (diffuse + specular);
        }

        float kr = mat->getKr();
        if (kr > 0) {
            Ray reflectedRay = {.raytype=SECONDARY, .o = hit.point, .d = r.d - 2*(hit.normal.dotProduct(r.d))*hit.normal};
            pointColour = (1-kr)*pointColour + kr*colourAtHit(reflectedRay, scene, nbounces-1);
        }
        return pointColour;
    }

    // If ray doesn't hit anything
    return scene->getBackgroundColour();
}


/**
 * Tonemaps the rendered image (conversion of linear RGB values [0-1] to low dynamic range [0-255]
 *
 * @param pixelbuffer the array of size width*height containing linear RGB pixel values
 *
 * @return the tonemapped image
 */
Vec3f* RayTracer::tonemap(Vec3f* pixelbuffer, int length){

	//---------tonemapping function to be filled--------

    for (int i = 0; i < length; i++) {
        Vec3f colour = *(pixelbuffer+i);

        // map from 1-inf to 0-1
        Vec3f inRange = Vec3f(colour.x/(colour.x+1), colour.y/(colour.y+1), colour.z/(colour.z+1));  // Use rindheart

        // linear space to gamma space
//        Vec3f gammaCorrected = Vec3f(powf(inRange.x, 1/2.2), powf(inRange.y, 1/2.2), powf(inRange.z, 1/2.2));
//        *(pixelbuffer+i) = gammaCorrected * 255;
        *(pixelbuffer+i) = inRange * 255;

    }
	return pixelbuffer;

}




} //namespace rt


