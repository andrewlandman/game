#include "Scene.hpp"

Scene::Scene(scene::ISceneManager* sceneManager)
    :
    mSceneManager(sceneManager)
{}

void Scene::initialize() {
    // Add spheres
    mNode1 = mSceneManager->addSphereSceneNode(5);
    mNode1->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode1->getMaterial(0).EmissiveColor.set(255, 255, 0, 0);
    mNode1->setPosition(core::vector3df(100, 0, 0));

    mNode2 = mSceneManager->addSphereSceneNode(5);
    mNode2->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode2->getMaterial(0).EmissiveColor.set(255, 0, 0, 255);
    mNode2->setPosition(core::vector3df(-100, 0, 0));

    // Add cube
    scene::ISceneNode* cube = mSceneManager->addCubeSceneNode();
    cube->setMaterialFlag(video::EMF_LIGHTING, false);
    cube->setPosition(core::vector3df(0,0,100));

    // Add skybox
    scene::IMeshSceneNode* skybox = mSceneManager->addCubeSceneNode(1000);
    skybox->setMaterialFlag(video::EMF_LIGHTING, true);
    skybox->getMaterial(0).EmissiveColor.set(255, 40, 40, 40);
    skybox->getMaterial(0).BackfaceCulling = true;
    skybox->setPosition(core::vector3df(0, 0, 0));
    mSceneManager->getMeshManipulator()->flipSurfaces(skybox->getMesh());
    mSceneManager->getMeshManipulator()->recalculateNormals(skybox->getMesh());

    // Add light
    scene::ISceneNode* light = mSceneManager->addLightSceneNode(
        0,
        core::vector3df(500, 0, 100),
        video::SColorf(1.0, 1.0, 1.0),
        250
    );
}

void Scene::update(uint32_t dt) {
    core::vector3df pos1 = mNode1->getPosition();
    pos1.X -= 0.01*dt;
    mNode1->setPosition(pos1);

    core::vector3df pos2 = mNode2->getPosition();
    pos2.X += 0.01*dt;
    mNode2->setPosition(pos2);
}
