#include "irrlicht.h"

#include <iostream>
#include <time.h>

#include "Camera.hpp"
#include "EventReceiver.hpp"
#include "InputHandler.hpp"
#include "Scene.hpp"

using namespace irr;

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

    Scene scene(sceneManager);
    scene.initialize();

    Camera camera(sceneManager, irr::core::vector3df(0.0, 0.0, -200.0));
    InputHandler inputHandler(receiver, camera);

    uint32_t deltaTime   = 0;
    uint32_t lastTime    = device->getTimer()->getTime();
    uint32_t targetTime  = 30;
    uint32_t accumulator = 0;

    while(device->run())
    {
        // output
        driver->beginScene(true, true, video::SColor(0,0,0,0));
        sceneManager->drawAll();
        driver->endScene();

        deltaTime = device->getTimer()->getTime() - lastTime;
        lastTime += deltaTime;
        accumulator += deltaTime;

        // input
        inputHandler.handleInput();

        // update
        while (accumulator > targetTime) {
            std::cout << targetTime << " " << accumulator << std::endl;
            scene.update(targetTime);
            accumulator -= targetTime;
        }
    }

    device->drop();

    return 0;
}
