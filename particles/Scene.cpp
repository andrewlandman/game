#include "Scene.hpp"

void generateSpheres(scene::ISceneManager* sceneManager) {
    for (size_t i = 0; i < 100; i++) {
        scene::IMeshSceneNode* node = sceneManager->addSphereSceneNode(5);
        node->setMaterialFlag(video::EMF_LIGHTING, true);
        node->getMaterial(0).EmissiveColor.set(
            255,
            rand() % 255,
            rand() % 255,
            rand() % 255
        );
        node->setPosition(core::vector3df(
            rand() % 100,
            rand() % 100,
            rand() % 100
        ));
    }
}

Scene::Scene(scene::ISceneManager* sceneManager)
    :
    mSceneManager(sceneManager)
{}

void Scene::initialize() {
    // Add spheres
    generateSpheres(mSceneManager);

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

void Scene::update() {
}
