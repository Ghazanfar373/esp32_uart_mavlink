ESP32-ArduPilot Telemetry Bridge
This project provides a robust solution for a companion computer (ESP32) to send custom telemetry data to an ArduPilot flight controller. It uses the MAVLink protocol to transmit real-time fuel and engine status, enabling enhanced monitoring and decision-making during flight missions.

Key Features
Custom MAVLink Messaging: Transmits data using the NAMED_VALUE_FLOAT and NAMED_VALUE_INT MAVLink messages, ensuring compatibility with standard ground control stations (GCS) like Mission Planner and QGroundControl.

Real-time Monitoring: Allows for the display of custom parameters (e.g., fuel flow, engine status) directly on the GCS's data tab.

Hardware Agnostic: While developed and tested on an ESP32 and CUAVv5, the MAVLink communication principles are applicable to any microcontroller capable of serial communication.

Clear Code Structure: The code is modular and well-commented, making it easy to adapt for different sensors and data types.

Hardware Requirements
Microcontroller: ESP32 board (or any other Arduino-compatible board with multiple hardware serial ports).

Flight Controller: ArduPilot-based flight controller (e.g., CUAVv5).

Sensors: Appropriate sensors for measuring fuel and engine data (e.g., flow meters, temperature sensors, pressure sensors).

Getting Started
Clone the Repository:

git clone [https://github.com/Ghazanfar373/esp32_uart_mavlink.git]

Install Libraries:

Open the Arduino IDE.

Install the MAVLink library via the Library Manager.

Hardware Connections:

Connect the ESP32's TX pin to the ArduPilot's RX pin on an available serial port (e.g., Telem1).

Connect the ESP32's RX pin to the ArduPilot's TX pin.

Connect GND to GND.

ArduPilot Configuration:

In Mission Planner or QGroundControl, set the SERIAL1_PROTOCOL parameter to 1 (MAVLink1) or 2 (MAVLink2) and SERIAL1_BAUD to 115200.

View Data:

Once connected, navigate to the Data tab in Mission Planner.

Right-click on the data pane and select your custom parameters by name.

Code Explanation
The code uses a series of functions to manage MAVLink communication:

setup(): Initializes the serial port and sets MAVLink system IDs.

loop(): Manages the timing for sending MAVLink messages, including heartbeats and custom data packets.

send_named_value_float() / send_named_value_int(): Dedicated functions for packaging and sending custom sensor data with descriptive names, allowing for seamless integration with the GCS.

Acknowledgements
This project was built upon the foundational work and examples from the following repository:

AndersonRayner/arduino_mavlink: https://github.com/AndersonRayner/arduino_mavlink/