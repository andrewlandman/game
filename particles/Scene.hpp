#ifndef SCENE_HPP
#define SCENE_HPP

#include "irrlicht.h"

using namespace irr;
using namespace scene;

class Scene {
public:
    Scene(scene::ISceneManager* sceneManager);
    void initialize();
    void update();
private:
    scene::ISceneManager* mSceneManager; 
};

#endif // SCENE_HPP
