/*
 * Camera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <geometry.h>
#include "rapidjson/document.h"
#include "RayHitStructs.h"


using namespace rapidjson;

namespace rt{

class Camera{
public:

	//
	// Constructors
	//
	Camera(){};
	Camera(int height, int width, int fov, Vec3f position, Vec3f lookat, Vec3f up);

	//
	// Destructor
	//
	virtual ~Camera();


	//
	// factory function : returns camera instance dynamically based on camera specifications
	//
	static Camera* createCamera(Value& cameraSpecs);


	//
	// print function (to be implemented by the subclasses )
	//
	virtual void printCamera()=0;



	//
	// other camera functions (to complete)
	//

    virtual Ray castRay(int xPixel, int yPixel)=0;


	//
	// Getters and Setters
	//
	int getHeight() const {
		return m_height;
	}

	int getWidth() const {
		return m_width;
	}


    int getFov() const {
        return m_fov;
    }

    Vec3f getPosition() const {
        return m_position;
    }

    Vec3f getLookat() const {
        return m_lookat;
    }

    Vec3f getUp() const {
        return m_up;
    }

protected:

	//
	//camera members
	//
	int m_height;
	int m_width;
	int m_fov; //field of view
    Vec3f m_position;
    Vec3f m_lookat;
    Vec3f m_up;

    Matrix44f cameraToWorld;

};

} //namespace rt



#endif /* CAMERA_H_ */
