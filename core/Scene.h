/*
 * Scene.h
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "rapidjson/document.h"

#include "core/LightSource.h"
#include "core/Shape.h"


using namespace rapidjson;

namespace rt{

class Scene {
public:

	Scene(){};

	void createScene(Value& scenespecs);

    std::vector<Shape*>& getShapes(){
        return shapes;
    }

    std::vector<LightSource*>& getLightSources() {
        return lightSources;
    }

    Vec3f getBackgroundColour() {
        return backgroundColour;
    }



private:

    Vec3f backgroundColour;
	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;

};

} //namespace rt



#endif /* SCENE_H_ */
