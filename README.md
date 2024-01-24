# Joystick-Controlled FastDDS Project

## Overview
This project implements a system where joystick inputs are read and published using FastDDS to control devices like motor drivers or PLCs. It's designed to demonstrate the integration of SDL2 for joystick handling and FastDDS for efficient data communication.

## Dependencies
- [SDL2](https://www.libsdl.org/): Used for handling joystick inputs.
- [Fast DDS](https://www.eprosima.com/index.php/products-all/eprosima-fast-dds): A C++ implementation of the DDS (Data Distribution Service) standard for high-performance, real-time data exchange.

## Getting Started

### Prerequisites
- Install SDL2: Follow instructions on the [SDL website](https://www.libsdl.org/download-2.0.php).
- Install FastDDS: Follow the [FastDDS installation guide](https://fast-dds.docs.eprosima.com/en/latest/installation/binaries/binaries_linux.html).

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name

2. Create a build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..

3. Compile the project:
   ```bash
   cmake --build .

### Usage
Run the compiled executable to start reading joystick inputs and publishing them over DDS:
    ```bash
    ./JoystickFastDDS

## Components
### JoystickHandler
Purpose: Handles joystick inputs using SDL2.
Functionality: Initializes the joystick, reads button states and axis positions, and applies a deadzone for axis inputs.
Interaction: Provides the current state of the joystick to be published over DDS.
### DDSPublisher
Purpose: Publishes joystick data using FastDDS.
Functionality: Sets up DDS participants, publishers, and data writers to send joystick data to subscribed listeners.
Interaction: Takes the joystick data from JoystickHandler and publishes it over DDS.

### main.cpp
Purpose: Integrates JoystickHandler and DDSPublisher.
Functionality: Continuously reads joystick inputs and publishes them at a predefined rate using DDS.
Interaction: Orchestrates the data flow from the joystick to DDS and controls the publishing rate.

## DDS Topics and Message Types

The following table lists the DDS topics used in the project along with their corresponding message types:

| Topic Name     | Message Type   | Description                                   |
| -------------- | -------------- | --------------------------------------------- |
| `JoystickData` | `JoystickData` | Publishes the state of joystick inputs.       |
|                |                |                                               |

Each topic is used for a specific purpose within the FastDDS communication framework.

## Contributing
Contributions to this project are welcome! Please read our Contributing Guidelines for more information.

## License
This project is licensed under the MIT License.

## Contact
Project Link: https://github.com/ietamaher/JoystickFastDDS
