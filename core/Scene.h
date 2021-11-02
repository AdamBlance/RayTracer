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

    static Vec3f toVec3f(GenericArray<false, GenericValue<UTF8<>>::ValueType> const &json_array);

private:

	std::vector<LightSource*> lightSources;
	std::vector<Shape*> shapes;

};

} //namespace rt



#endif /* SCENE_H_ */
