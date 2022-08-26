#include "Camera.hpp"
#include "EventReceiver.hpp"
#include "InputHandler.hpp"

InputHandler::InputHandler(const EventReceiver& receiver, Camera& camera)
    :
    mReceiver(receiver),
    mCamera(camera)
{}

void InputHandler::handleInput() {
    // direction control
    if(mReceiver.IsKeyDown(irr::KEY_LEFT)) {
        mCamera.roll(0.1);
    }
    if(mReceiver.IsKeyDown(irr::KEY_RIGHT)) {
        mCamera.roll(-0.1);
    }
    if(mReceiver.IsKeyDown(irr::KEY_UP)) {
        mCamera.pitch(0.1);
    }
    if(mReceiver.IsKeyDown(irr::KEY_DOWN)) {
        mCamera.pitch(-0.1);
    }
    if(mReceiver.IsKeyDown(irr::KEY_KEY_A)) {
        mCamera.turn(-0.1);
    }
    if(mReceiver.IsKeyDown(irr::KEY_KEY_D)) {
        mCamera.turn(0.1);
    }

    // movement control
    if(mReceiver.IsKeyDown(irr::KEY_KEY_W)) {
        mCamera.move(core::vector3df(0,0,0.1));
    }
    if(mReceiver.IsKeyDown(irr::KEY_KEY_S)) {
        mCamera.move(core::vector3df(0,0,-0.1));
    }

    mCamera.update(core::vector3df(0,0,0));
}
