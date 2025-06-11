# ESP32 Air Quality Monitoring System

This project is an **Air Quality Monitoring System** built using an **ESP32** microcontroller. It integrates multiple sensors to measure **temperature**, **humidity**, **dust (PM2.5)**, and **air quality** (gases like CO and NH₃), and displays real-time data on an I2C LCD.

## Features

- 📡 Real-time temperature and humidity using **DHT22**
- 🏭 Gas concentration readings from **MQ135** and **MQ7**
- 🌫️ Dust particle measurement using **GP2Y1014AU**
- 📟 Clear 20x4 I2C LCD Display for output
- 📲 Serial output for debugging or further data logging

## Components Used

| Component        | Description                          |
|------------------|--------------------------------------|
| ESP32 Dev Board  | Main microcontroller                 |
| DHT22            | Temperature and humidity sensor      |
| MQ135            | Air quality sensor (NH₃, CO₂, etc.)  |
| MQ7              | Carbon Monoxide sensor               |
| GP2Y1014AU       | Optical dust sensor (PM2.5)          |
| 20x4 I2C LCD     | Display for sensor values            |
| Resistors, Capacitor | For dust sensor signal smoothing |
| Breadboard & Wires | Circuit connections                |

## Wiring Overview

- **DHT22**: GPIO 4
- **MQ135**: GPIO 34
- **MQ7**: GPIO 32
- **Dust Sensor**:
  - LED Control: GPIO 2
  - Analog Output: GPIO 35
- **LCD I2C**: SDA/SCL to ESP32 I2C pins (usually GPIO 21 and 22)

## How to Use

1. **Upload** the `final.cpp` code to your ESP32 using Arduino IDE or PlatformIO.
2. **Connect** all sensors and LCD as per the pin configuration.
3. Open **Serial Monitor** at 115200 baud rate to view live data.
4. Monitor the **20x4 LCD** for real-time environmental readings.

## Installation

1. Install the following libraries in Arduino IDE:
   - `DHT sensor library by Adafruit`
   - `Adafruit Unified Sensor`
   - `LiquidCrystal_I2C` (or compatible)

2. Upload the code and power the ESP32.

## Sample Output
- Air Quality Monitoring System
- T: 36.5°C H: 60%
- Air Quality : 18
- CO Level : 90
- Dust Level : 496
 

## Notes

- Ensure different analog sensors are connected to **separate ADC pins**.
- Use proper **voltage dividers** or **smoothing capacitors** for dust sensor accuracy.
- LCD I2C address might differ (try 0x27 or 0x3F).


© 2025 Sayan Chowdhury

