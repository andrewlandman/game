#ifndef SCENE_HPP
#define SCENE_HPP

#include "irrlicht.h"

using namespace irr;
using namespace scene;

class Scene {
public:
    Scene(scene::ISceneManager* sceneManager);
    void initialize();
    void update(uint32_t dt);
private:
    scene::ISceneManager* mSceneManager; 
    scene::IMeshSceneNode* mNode1;
    scene::IMeshSceneNode* mNode2;
};

#endif // SCENE_HPP
