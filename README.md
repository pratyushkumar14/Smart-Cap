# Smart Assistive Cap using ESP32 and BLE

A wearable assistive system designed to help visually impaired users detect nearby obstacles using an ultrasonic sensor. The system provides real-time alerts using a buzzer and Bluetooth Low Energy (BLE) notifications to a mobile device.

---

## 🔍 Problem Statement
Visually impaired individuals face difficulties in detecting obstacles while walking, especially in unfamiliar environments. Traditional aids have limited feedback mechanisms.

---

## 💡 Solution Overview
This project implements a **Smart Assistive Cap** that:
- Detects obstacles using an ultrasonic sensor
- Alerts the user with distance-based buzzer patterns
- Sends warning messages to a smartphone via BLE

---

## ⚙️ Features
- Real-time obstacle detection
- Distance-based buzzer alerts
- BLE notification support
- Non-blocking ESP32 firmware
- Wearable and low-power design

---

## 🛠 Hardware Components
- ESP32 Development Board
- HC-SR04 Ultrasonic Sensor
- Active Buzzer
- Jumper Wires
- Power Source (Battery/USB)

---

## 🔌 Pin Connections

| ESP32 Pin | Component |
|---------|----------|
| GPIO 17 | Ultrasonic TRIG |
| GPIO 16 | Ultrasonic ECHO |
| GPIO 26 | Buzzer |

---

## 📡 BLE Configuration
- **Device Name:** Smart_Cap  
- **Service UUID:** `12345678-1234-1234-1234-1234567890ab`  
- **Characteristic UUID:** `abcdefab-1234-5678-1234-abcdefabcdef`  

---

## 🧠 Working Principle
1. ESP32 sends a trigger pulse to the ultrasonic sensor
2. Echo pulse duration is measured
3. Distance is calculated based on sound velocity
4. Alerts are generated based on distance
5. BLE notifications are sent to a connected smartphone

---

## 🚨 Alert Logic

| Distance (cm) | Alert Type |
|--------------|-----------|
| ≤ 50 | Continuous buzzer + Danger message |
| ≤ 100 | Fast beep + Warning |
| ≤ 150 | Slow beep + Nearby obstacle |
| > 150 | Path clear |

---

## 📱 Mobile Application
Any generic BLE scanner app (e.g., nRF Connect) can be used to receive notifications.

---

## 🚀 Future Improvements
- Vibration motor instead of buzzer
- Mobile app with voice alerts
- GPS integration
- Battery optimization
- AI-based obstacle classification

---

## 🎓 Use Cases
- Assistive technology for visually impaired
- Wearable safety devices
- IoT-based obstacle detection

---

## 📜 License
This project is licensed under the MIT License.
