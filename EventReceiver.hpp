#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include "irrlicht.h"

class EventReceiver : public irr::IEventReceiver {
public:
    EventReceiver();
    bool OnEvent(const irr::SEvent &event) override;
    bool IsKeyDown(irr::EKEY_CODE keyCode) const; 
private:
    bool keys[irr::KEY_KEY_CODES_COUNT];
};

#endif // EVENT_RECEIVER_HPP
