#include "irrlicht.h"

#include <time.h>

#include "Camera.hpp"
#include "EventReceiver.hpp"

using namespace irr;

void handleInput(const EventReceiver& receiver, Camera& camera) {
    // direction control
    if(receiver.IsKeyDown(irr::KEY_LEFT)) {
        camera.roll(0.1);
    }
    if(receiver.IsKeyDown(irr::KEY_RIGHT)) {
        camera.roll(-0.1);
    }
    if(receiver.IsKeyDown(irr::KEY_UP)) {
        camera.pitch(0.1);
    }
    if(receiver.IsKeyDown(irr::KEY_DOWN)) {
        camera.pitch(-0.1);
    }
    if(receiver.IsKeyDown(irr::KEY_KEY_A)) {
        camera.turn(-0.1);
    }
    if(receiver.IsKeyDown(irr::KEY_KEY_D)) {
        camera.turn(0.1);
    }

    // movement control
    if(receiver.IsKeyDown(irr::KEY_KEY_W)) {
        camera.move(core::vector3df(0,0,0.1));
    }
    if(receiver.IsKeyDown(irr::KEY_KEY_S)) {
        camera.move(core::vector3df(0,0,-0.1));
    }

    camera.update(core::vector3df(0,0,0));
}

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

void initScene(scene::ISceneManager* sceneManager) {
    // Add spheres
    generateSpheres(sceneManager);

    // Add cube
    scene::ISceneNode* cube = sceneManager->addCubeSceneNode();
    cube->setMaterialFlag(video::EMF_LIGHTING, false);
    cube->setPosition(core::vector3df(0,0,100));

    // Add skybox
    scene::IMeshSceneNode* skybox = sceneManager->addCubeSceneNode(1000);
    skybox->setMaterialFlag(video::EMF_LIGHTING, true);
    skybox->getMaterial(0).EmissiveColor.set(255, 40, 40, 40);
    skybox->getMaterial(0).BackfaceCulling = true;
    skybox->setPosition(core::vector3df(0, 0, 0));
    sceneManager->getMeshManipulator()->flipSurfaces(skybox->getMesh());
    sceneManager->getMeshManipulator()->recalculateNormals(skybox->getMesh());

    // Add light
    scene::ISceneNode* light = sceneManager->addLightSceneNode(
        0,
        core::vector3df(500, 0, 100),
        video::SColorf(1.0, 1.0, 1.0),
        250
    );
}

int main()
{
    srand(time(NULL));

    EventReceiver receiver;
    IrrlichtDevice* device = createDevice(
        video::EDT_OPENGL,
        core::dimension2d<u32>(800, 600),
        32,
        false,
        false,
        false,
        &receiver
    );

    device->setResizable(true);

    video::IVideoDriver*  driver       = device->getVideoDriver();
    scene::ISceneManager* sceneManager = device->getSceneManager();

    initScene(sceneManager);
    Camera camera(sceneManager);

    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(0,0,0,0));
        sceneManager->drawAll();

        handleInput(receiver, camera);

        driver->endScene();
    }

    device->drop();

    return 0;
}
