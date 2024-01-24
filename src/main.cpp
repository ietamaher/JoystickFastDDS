#include "joystick_handler.h"
#include "dds_publisher.h"
#include <chrono>
#include <thread>

int main() {
    JoystickHandler joystick;
    DDSPublisher ddsPublisher;

    // Define the rate at which to publish joystick data (e.g., 60 times per second)
    const std::chrono::milliseconds rate(1000 / 60); 

    while (true) {
        auto start = std::chrono::steady_clock::now();

        joystick.update();

        JoystickData data;
        data.buttonStates(joystick.getButtonStates());
        // Convert axis states from float to double
        std::vector<float> axisStatesFloat = joystick.getAxisStates();
        std::vector<double> axisStatesDouble(axisStatesFloat.begin(), axisStatesFloat.end());
        data.axisStates(axisStatesDouble);
        ddsPublisher.publish(data);

        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - start;
        if (elapsed < rate) {
            std::this_thread::sleep_for(rate - elapsed); // Sleep to maintain the publishing rate
        }
    }

    return 0;
}

