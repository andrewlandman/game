#ifndef SCENE_HPP
#define SCENE_HPP

#include "irrlicht.h"

using namespace irr;
using namespace scene;
using namespace video;

class Scene {
public:
    Scene(scene::ISceneManager* sceneManager,
          video::IVideoDriver*  driver);
    void initialize();
    void draw();
    void update(uint32_t dt);
private:
    video::IVideoDriver* mDriver;
    scene::ISceneManager* mSceneManager; 
    scene::IMeshSceneNode* mNode1;
    scene::IMeshSceneNode* mNode2;
    scene::ISceneNode* mCube;
    scene::ISceneNode* mPlane;
    video::ITexture* mRT;
    scene::ICameraSceneNode* mFixedCamera;
};

#endif // SCENE_HPP
