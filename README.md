# Automatic-Railway-Crossing-System
A real-time embedded safety system using microcontrollers and IR sensors for automated gate control.
# Automatic Railway Crossing System

## 📌 Project Overview
An automated safety solution designed to eliminate manual errors at railway crossings. The system uses IR sensors to detect approaching trains and triggers a microcontroller to operate gate actuators in real-time.

## 🛠️ Hardware Components
* Microcontroller (Arduino/ATMega328P)
* IR Sensor Modules (for train detection)
* Servo Motors / DC Motors (for gate actuation)
* Buzzer & LEDs (for signaling)

## 💻 Software & Logic
* **Language:** Embedded C++
* **Logic:** The system uses interrupt-driven sensing to ensure zero-latency response when a train is detected.
* **Algorithm:** 1. Sensor A detects train -> Activate Buzzer/LEDs -> Close Gates.
  2. Sensor B detects train has passed -> Open Gates -> Reset System.

## 🚀 How to Use
1. Connect hardware as per the circuit diagram in `/docs`.
2. Upload the code from `/src` using the Arduino IDE or VS Code.
3. Power the system and test sensor calibration.

## 🏆 Achievements
* Successfully implemented as a Mini-Project at **SIT Tumkur (NBA Accredited)**.
