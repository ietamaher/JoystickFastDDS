#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include <SDL.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <thread>

#include <iostream>

class JoystickHandler {
public:
    JoystickHandler(float deadzone = 0.05, int updateRate = 60, int connectionTimeout = 30);
    ~JoystickHandler();
    void update();
    std::vector<int> getButtonStates() const;
    std::vector<float> getAxisStates() const;
    std::vector<int> getHatStates() const;

    void setDeadzone(float deadzone);
    void setUpdateRate(int rate);
    bool running = true;


private:
    float deadzone;
    int updateRate;
    SDL_Joystick* joystick;
    std::vector<int> buttonStates;
    std::vector<float> axisStates;
    std::vector<int> hatStates;
};

#endif // JOYSTICK_HANDLER_H

