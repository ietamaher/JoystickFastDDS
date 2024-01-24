#include "joystick_handler.h"

JoystickHandler::JoystickHandler(float deadzone, int updateRate)
    : deadzone(deadzone), updateRate(updateRate), joystick(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    if (SDL_NumJoysticks() < 1) {
        throw std::runtime_error("No joysticks connected!");
    }

    joystick = SDL_JoystickOpen(0);
    if (joystick == nullptr) {
        throw std::runtime_error("Failed to open joystick! SDL_Error: " + std::string(SDL_GetError()));
    }

    buttonStates.resize(SDL_JoystickNumButtons(joystick), 0);
    axisStates.resize(SDL_JoystickNumAxes(joystick), 0.0f);
    hatStates.resize(SDL_JoystickNumHats(joystick), SDL_HAT_CENTERED);
}

JoystickHandler::~JoystickHandler() {
    if (joystick) {
        SDL_JoystickClose(joystick);
    }
    SDL_Quit();
}

void JoystickHandler::setDeadzone(float dz) {
    deadzone = dz;
}

void JoystickHandler::setUpdateRate(int rate) {
    updateRate = rate;
}

void JoystickHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYAXISMOTION:
                if ((event.jaxis.value < -3200) || (event.jaxis.value > 3200)) {
                    float value = event.jaxis.value / 32767.0f;
                    if (std::abs(value) >= deadzone) {
                        axisStates[event.jaxis.axis] = value;
                    }
                }
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                buttonStates[event.jbutton.button] = event.jbutton.state;
                break;
            case SDL_JOYHATMOTION:
                hatStates[event.jhat.hat] = event.jhat.value;
                break;
        }
    }
}

std::vector<int> JoystickHandler::getButtonStates() const {
    return buttonStates;
}

std::vector<float> JoystickHandler::getAxisStates() const {
    return axisStates;
}

std::vector<int> JoystickHandler::getHatStates() const {
    return hatStates;
}