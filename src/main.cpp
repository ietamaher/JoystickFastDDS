#include "joystick_handler.h"
#include "dds_publisher.h"
#include <chrono>
#include <thread>
#include <csignal>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>

static bool running; // Declaration

struct Config {
    float deadzone;
    int updateRate;
    int connectionTimeout;
    int publishRate;
};

Config loadConfig(const std::string& filename) {
    YAML::Node config = YAML::LoadFile(filename);

    Config cfg;
    cfg.deadzone = config["joystick"]["deadzone"].as<float>();
    cfg.updateRate = config["joystick"]["updateRate"].as<int>();
    cfg.connectionTimeout = config["joystick"]["connectionTimeout"].as<int>();
    cfg.publishRate = config["publish"]["rate"].as<int>();

    return cfg;
}

volatile std::sig_atomic_t signalReceived = 0;

void signalHandler(int signal) {
    std::cout << "Signal " << signal << " received. Preparing to exit..." << std::endl;
    signalReceived = 1;
}

int main() {
    Config config = loadConfig("config.yaml");

    std::signal(SIGINT, signalHandler); // Register signal handler for graceful exit

    try {
        JoystickHandler joystick(config.deadzone, config.updateRate, config.connectionTimeout);
        DDSPublisher ddsPublisher;

        // Define the rate at which to publish joystick data (e.g., 60 times per second)
        const std::chrono::milliseconds rate(1000 / config.publishRate);  

        while (running) {
            auto start = std::chrono::steady_clock::now();

            joystick.update(); // This will handle reconnection internally

            JoystickData data;

            data.buttonStates(joystick.getButtonStates());
            data.hatStates(joystick.getHatStates());

            // Convert axis states from float to double
            std::vector<float> axisStatesFloat = joystick.getAxisStates();
            std::vector<double> axisStatesDouble(axisStatesFloat.begin(), axisStatesFloat.end());
            data.axisStates(axisStatesDouble);

            ddsPublisher.publish(data); // Publish joystick data

            auto end = std::chrono::steady_clock::now();
            auto elapsed = end - start;
            if (elapsed < rate) {
                std::this_thread::sleep_for(rate - elapsed); // Sleep to maintain the publishing rate
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
        return 1; // Return an error code
    }

    std::cout << "Application exiting ..." << std::endl;
    return 0; // Successful exit
}

