# ESP32 Smart Traffic Light Controller 🚦

## Project Overview

An ESP32-based smart traffic light controller developed using Embedded C, ESP-IDF, and PlatformIO. The project simulates a vehicle traffic system with pedestrian crossing support using Wokwi.

## Features

* Automatic vehicle traffic light sequence
* Pedestrian crossing request button
* Separate pedestrian red and green LEDs
* Buzzer alert during pedestrian crossing
* Countdown messages in the program
* Virtual circuit simulation using Wokwi

## Hardware Components (Simulated)

* ESP32 DevKit
* Red, yellow, and green LEDs for vehicle signals
* Red and green LEDs for pedestrian signals
* Push button
* Buzzer
* Current-limiting resistors

## Technologies Used

* Embedded C
* ESP32
* ESP-IDF
* PlatformIO
* Wokwi Simulator
* Visual Studio Code

## Working Principle

The vehicle traffic lights operate in a predefined sequence. A pedestrian can request to cross using a push button. When the request is accepted, the vehicle signal changes to red, the pedestrian green LED turns on, and the buzzer provides an audible alert during the crossing phase.

## Testing

The project was developed and tested using the Wokwi ESP32 simulator. No physical hardware was required for simulation.

## Future Improvements

* Add a countdown display for pedestrians
* Add a flashing warning before the crossing phase ends
* Improve pedestrian request handling
* Add an emergency vehicle priority feature

## Author

Embedded Systems Learner
