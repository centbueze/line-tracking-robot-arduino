# 🤖 Line Tracking Robot with Arduino

A simple **line-following robot** built using an **Arduino UNO**, **IR sensors**, and **DC motors**.  
The robot detects and follows a black line on a white surface (or vice versa) using infrared sensors.  

---

## 📌 Project Overview
- 🧠 **Microcontroller**: Arduino UNO  
- 👀 **Sensors**: IR line sensors (2 / 3 / 5 depending on design)  
- 🚗 **Actuators**: DC motors with motor driver (L298N / L293D)  
- 🔋 **Power**: 7.4V Li-ion / 9V battery / 12V supply  
- 🎯 **Goal**: Robot follows a path automatically by detecting contrast between line & background.  

---

## 📂 Repository Structure
```bash
line-tracking-robot/
│── LineTrackingRobot.ino   # Arduino sketch
│── circuit_diagram.png     # Circuit wiring diagram
│── README.md               # Documentation
