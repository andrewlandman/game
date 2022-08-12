#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

class InputHandler {
public:
    InputHandler(const EventReceiver& receiver, Camera& camera);
    void handleInput();
private:
    const EventReceiver& mReceiver;
    Camera& mCamera;
};

#endif // INPUT_HANDLER_HPP
