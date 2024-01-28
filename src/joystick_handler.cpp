#include "joystick_handler.h"


 

JoystickHandler::JoystickHandler(float deadzone, int updateRate, int connectionTimeout)
    : deadzone(deadzone), updateRate(updateRate), joystick(nullptr) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
    }
 

    int attempts = 0;
    while (SDL_NumJoysticks() < 1 && running && attempts < connectionTimeout) {
        std::cout << "Waiting for joystick connection... Attempt " << (attempts + 1) << "/" << connectionTimeout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait 1 second before checking again
        SDL_JoystickUpdate(); // Update the state of all opened joysticks
        attempts++;
    }


    if (SDL_NumJoysticks() < 1) {
        std::cout << "No joystick connected after waiting for " << connectionTimeout << " seconds. Exiting." << std::endl;
        running = false;
        return; // Exit the constructor to avoid further execution
    }

    joystick = SDL_JoystickOpen(0);
    if (joystick == nullptr) {
        throw std::runtime_error("Failed to open joystick! SDL_Error: " + std::string(SDL_GetError()));
    }

    buttonStates.resize(SDL_JoystickNumButtons(joystick), 0);
    axisStates.resize(SDL_JoystickNumAxes(joystick), 0.0f);
    hatStates.resize(SDL_JoystickNumHats(joystick), SDL_HAT_CENTERED);

    std::cout << "Joystick connected and initialized." << std::endl;

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

    if (!joystick || SDL_JoystickGetAttached(joystick) == SDL_FALSE) {
        std::cout << "Joystick disconnected. Attempting reconnection..." << std::endl;
        joystick = nullptr; // Reset joystick to nullptr to ensure safe reconnection attempt

        // Attempt reconnection
        for (int i = 0; i < SDL_NumJoysticks() && !joystick; ++i) {
            joystick = SDL_JoystickOpen(i);
            if (joystick) {
                std::cout << "Joystick reconnected." << std::endl;
                // Re-initialize state vectors to match the newly connected joystick
                buttonStates.resize(SDL_JoystickNumButtons(joystick), 0);
                axisStates.resize(SDL_JoystickNumAxes(joystick), 0.0f);
                hatStates.resize(SDL_JoystickNumHats(joystick), SDL_HAT_CENTERED);
            }
        }
        if (!joystick) return; // If reconnection unsuccessful, exit the update
    }

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (!joystick) break; // Safety check to ensure joystick is connected

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




