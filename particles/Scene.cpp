#include "Scene.hpp"
#include "Quaternion.hpp"
#include <iostream>

Scene::Scene(scene::ISceneManager* sceneManager)
    :
    mSceneManager(sceneManager)
{}

void Scene::initialize() {
    // Add spheres
    mNode1 = mSceneManager->addSphereSceneNode(5);
    mNode1->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode1->getMaterial(0).EmissiveColor.set(255, 255, 0, 0);
    mNode1->setPosition(core::vector3df(0, 0, 0));

    mNode2 = mSceneManager->addSphereSceneNode(5);
    mNode2->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode2->getMaterial(0).EmissiveColor.set(255, 0, 0, 255);
    mNode2->setPosition(core::vector3df(100, 0, 0));

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
    core::vector3df pos2 = mNode2->getPosition();

    auto q = Quaternion::fromAxisAngle(0.1, 0, 1, 0);
    q = q->rotate(pos2.X, pos2.Y, pos2.Z);
    pos2.X = q->mX;
    pos2.Y = q->mY;
    pos2.Z = q->mZ;

    mNode2->setPosition(pos2);
}
