#include "irrlicht.h"

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

    Camera camera(sceneManager);
    InputHandler inputHandler(receiver, camera);

    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(0,0,0,0));
        sceneManager->drawAll();
        driver->endScene();

        inputHandler.handleInput();
        scene.update();
    }

    device->drop();

    return 0;
}
