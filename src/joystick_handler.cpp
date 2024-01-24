

#include "joystick_handler.h"


/*JoystickHandler::JoystickHandler() {
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }

    if (SDL_NumJoysticks() < 1) {
        throw std::runtime_error("No joysticks connected!");
    }

    joystick = SDL_JoystickOpen(0); // Open the first joystick
    if (joystick == nullptr) {
        throw std::runtime_error("Failed to open joystick! SDL_Error: " + std::string(SDL_GetError()));
    }

    buttonStates.resize(SDL_JoystickNumButtons(joystick), 0);
    axisStates.resize(SDL_JoystickNumAxes(joystick), 0.0f);
}*/


JoystickHandler::JoystickHandler(float deadzone, int updateRate)
    : deadzone(deadzone), updateRate(updateRate) {
    // Initialize SDL for joystick support
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
        // Handle initialization error
        throw std::runtime_error("Failed to initialize SDL: " + std::string(SDL_GetError()));
    }

    // Open the first available joystick
    if (SDL_NumJoysticks() > 0) {
        SDL_Joystick* joy = SDL_JoystickOpen(0);
        if (joy == nullptr) {
            throw std::runtime_error("Failed to open joystick: " + std::string(SDL_GetError()));
        }
    } else {
        throw std::runtime_error("No joysticks connected!");
    }
    int numButtons = SDL_JoystickNumButtons(joystick);
    buttonStates.resize(numButtons, 0);

    int numAxes = SDL_JoystickNumAxes(joystick);
    axisStates.resize(numAxes, 0.0f);    
}

JoystickHandler::~JoystickHandler() {
    // Close all opened joysticks and quit SDL
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        SDL_JoystickClose(SDL_JoystickOpen(i));
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
    SDL_JoystickUpdate(); // Update the current state of the open joysticks

    for (int i = 0; i < SDL_JoystickNumButtons(joystick); ++i) {
        buttonStates[i] = SDL_JoystickGetButton(joystick, i);
    }

    for (int i = 0; i < SDL_JoystickNumAxes(joystick); ++i) {
        float value = SDL_JoystickGetAxis(joystick, i) / 32767.0f; // Normalize the axis value
        axisStates[i] = (std::abs(value) < deadzone) ? 0.0f : value; // Apply deadzone
    }
}

std::vector<int> JoystickHandler::getButtonStates() const {
    return buttonStates;
}

std::vector<float> JoystickHandler::getAxisStates() const {
    return axisStates;
}
