#include "EventReceiver.hpp"

EventReceiver::EventReceiver() {
    for (size_t i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
        keys[i] = false;
}

bool EventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return true;
    }
    return false;
}

bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const {
    return keys[keyCode];
}
