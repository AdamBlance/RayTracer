//
// Created by Adam on 10/11/2021.
//

#include "PPMReader.h"
#include <string>

namespace PPMReader {

    Vec3f* PPMReader(int width, int height, const std::string &filename) {

        std::fstream ppmFile;
        ppmFile.open(filename, std::ios::in);

        if (ppmFile.is_open()) {

            auto *loadedImage = new Vec3f[width * height];

            std::string magicNum;
            std::string gimpComment;
            std::string resolution;
            std::string maxVal;

            std::getline(ppmFile, magicNum);
            std::getline(ppmFile, gimpComment);
            std::getline(ppmFile, resolution);
            std::getline(ppmFile, maxVal);  // GIMP maxval is broken

            std::string r;
            std::string g;
            std::string b;

            for (int i = 0; i < width * height; i++) {
                std::getline(ppmFile, r);
                std::getline(ppmFile, g);
                std::getline(ppmFile, b);

                loadedImage[i] = Vec3f(powf(stof(r)/255, 2.2), powf(stof(g)/255, 2.2), powf(stof(b)/255, 2.2));
//                loadedImage[i] = Vec3f(powf(stof(r)/255, 1), powf(stof(g)/255, 1), powf(stof(b)/255, 1));
            }

            ppmFile.close();
            return loadedImage;

        } else {
            return nullptr;
        }

    }

} //namespace PPMReader