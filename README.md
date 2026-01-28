# Autonomous Wall Detection & Navigation System 🤖

An embedded systems project built on the **TI Tiva C Series (TM4C123GH6PM)** microcontroller. This system implements an autonomous robot capable of real-time wall detection, obstacle avoidance, and precise navigation using ultrasonic sensors.

## 🚀 Key Features

- **Autonomous Navigation**: intelligently navigates mazes or corridors without human intervention.
- **Real-Time Wall Following**: Uses PD-like control logic to maintain a constant distance from walls.
- **Obstacle Avoidance**: Detects frontal obstacles and executes 90° turns to reroute.
- **Bluetooth Control**: Supports remote command overrides (Start/Stop) via UART/Bluetooth module.
- **Modular Architecture**: Clean, driver-based code structure for easy maintenance and scalability.

## 🛠️ Hardware Specifications

- **Microcontroller**: Tiva C Series TM4C123GH6PM
- **Sensors**: 3x HC-SR04 Ultrasonic Sensors (Front, Left, Right)
- **Actuators**: DC Motors with PWM speed control
- **Communication**: HC-06/HC-05 Bluetooth Module (UART)

## 🔌 Pin Configuration

| Component | Pin Function | Tiva Pin |
|-----------|--------------|----------|
| **Left Motor** | PWM Speed | PC5 |
| | Direction 1 | PA2 |
| | Direction 2 | PD2 |
| **Right Motor** | PWM Speed | PC4 |
| | Direction 1 | PC4 |
| | Direction 2 | PB3 |
| **Sensors** | Front Trig/Echo | PD0 / PE5 |
| | Left Trig/Echo | PD7 / PA3 |
| | Right Trig/Echo | PB5 / PB0 |

## 🧩 Software Architecture

The software is designed with a modular approach, separating hardware abstraction from application logic:
- `main.cpp`: Implements the decision-making state machine.
- `src/motor.cpp`: Handles low-level PWM and direction control logic.
- `src/sensor.cpp`: Manages ultrasonic timing ranges and distance conversion.
- `include/config.h`: Centralized configuration for pins and tuning parameters.

## 🚀 Getting Started

1.  **Clone the Repository**:
    ```bash
    git clone https://github.com/Yousuf7788/MCI_Project_sp25.git
    ```
2.  **Open in IDE**: Import the project into Energia IDE or PlatformIO.
3.  **Upload**: Connect your Tiva C launchpad and upload the firmware.
4.  **Run**: Place the robot in a corridor and send 'G' via Bluetooth to start.

---
*Developed for the Microcontroller Interfacing Course (Spring 2025).*
