
#include "PLYReader.h"
#include <string>
#include <vector>

namespace PLYReader {

    std::vector<rt::Shape*>* PLYReader(const std::string &filename) {

        std::fstream plyFile;
        plyFile.open(filename, std::ios::in);

        if (plyFile.is_open()) {


            int n = 1000; // Max chars to read

            // Bunch of data we don't need at the start of file

            plyFile.ignore(n, '\n');  // "ply"
            plyFile.ignore(n, '\n');  // "format ascii 1.0"
            plyFile.ignore(n, '\n');  // "comment Created by Blender 2.93.4 - www.blender.org"

            plyFile.ignore(n, ' ');  // "element "
            plyFile.ignore(n, ' ');  // "vertex "

            std::string numVertsString;
            std::getline(plyFile, numVertsString, '\n');
            int numVerts = std::stoi(numVertsString);

//            std::cout << "num verts = " << numVerts << std::endl;

            plyFile.ignore(n, '\n');  // "property float x"
            plyFile.ignore(n, '\n');  // "property float y"
            plyFile.ignore(n, '\n');  // "property float z"
            plyFile.ignore(n, '\n');  // "property float s"
            plyFile.ignore(n, '\n');  // "property float t"

            plyFile.ignore(n, ' ');  // "element "
            plyFile.ignore(n, ' ');  // "face "

            std::string numFacesString;
            std::getline(plyFile, numFacesString, '\n');
            int numFaces = std::stoi(numFacesString);

//            std::cout << "num faces = " << numFaces << std::endl;


            plyFile.ignore(n, '\n');  // "property list uchar uint vertex_indices"
            plyFile.ignore(n, '\n');  // "end_header"

            // Vert + UV list begins

            std::string xStr;
            std::string yStr;
            std::string zStr;
            std::string uStr;
            std::string vStr;

            Vec3f verts[numVerts];
            Vec2f uvCoords[numVerts];

            // Populate list of verts and UV coords
            for (int i = 0; i < numVerts; i++) {
                std::getline(plyFile, xStr, ' ');
                std::getline(plyFile, yStr, ' ');
                std::getline(plyFile, zStr, ' ');
                std::getline(plyFile, uStr, ' ');
                std::getline(plyFile, vStr, '\n');

                verts[i] = Vec3f(std::stof(xStr), std::stof(yStr), std::stof(zStr));
                uvCoords[i] = Vec2f(std::stof(uStr), std::stof(vStr));
            }

            std::string v0Index;
            std::string v1Index;
            std::string v2Index;

            auto* triangles = new std::vector<rt::Shape*>();

//            std::cout << "size of triangle list = " << triangles->size() << std::endl;


            // Create list of triangles
            for (int i = 0; i < numFaces; i++) {
                plyFile.ignore(n, ' ');  // "3 "

                std::getline(plyFile, v0Index, ' ');
                std::getline(plyFile, v1Index, ' ');
                std::getline(plyFile, v2Index, '\n');

//                std::cout << "i = " << i << std::endl;


                triangles->push_back(new rt::Triangle(
                        verts[std::stoi(v0Index)], verts[std::stoi(v1Index)], verts[std::stoi(v2Index)],
                        uvCoords[std::stoi(v0Index)], uvCoords[std::stoi(v1Index)], uvCoords[std::stoi(v2Index)], nullptr));
            }

            plyFile.close();

//            std::cout << "size of triangle list after pushing triangles = " << triangles->size() << std::endl;


            return triangles;

        } else {
            // If file didn't open
            return nullptr;
        }

    }
        

} //namespace PLYReader