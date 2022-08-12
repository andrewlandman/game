#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "irrlicht.h"

using namespace irr;

using namespace scene;

class Camera {
public:
    Camera(scene::ISceneManager* sceneManager, irr::core::vector3df position);
    void update(irr::core::vector3df offset);
    void move(irr::core::vector3df vel);
    void rotate(irr::core::vector3df rot);
    void turn(irr::f32 rot);
    void pitch(irr::f32 rot);
    void roll(irr::f32 rot);
private:
    scene::ICameraSceneNode* mCamera;
    scene::ISceneNode* mNode; 
};

#endif // CAMERA_HPP
