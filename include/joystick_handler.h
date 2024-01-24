#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include <SDL.h>
#include <chrono>
#include <vector>
#include <string>  // For std::string
#include <stdexcept>  // For std::runtime_error
#include <cmath>  // For std::abs

class JoystickHandler {
public:
    JoystickHandler(float deadzone = 0.05, int updateRate = 60);
    ~JoystickHandler();
    void update();
    std::vector<int> getButtonStates() const;
    std::vector<float> getAxisStates() const;

    void setDeadzone(float deadzone);
    void setUpdateRate(int rate);

private:
    float deadzone;
    int updateRate;
    SDL_Joystick* joystick;  // Pointer to the SDL joystick
    std::vector<int> buttonStates;
    std::vector<float> axisStates;
    // Additional private members for timer or last update time
};

#endif // JOYSTICK_HANDLER_H

