# ESP32 Web-Controlled Servo Gate System

A real-time IoT control system built using the **WeMos D1 Mini ESP32** microcontroller. This project provisions the ESP32 as a standalone **Wi-Fi Access Point (AP)** hosting an embedded, responsive web server. Users can connect to the local Wi-Fi network and control a physical servo motor along with status indicator LEDs through an intuitive, modern web interface.

---

## Features

* **Standalone Wi-Fi Access Point**: Operates without requiring an external internet connection or router.
* **Embedded Web Server**: Delivers a sleek, modern, and responsive glassmorphism UI built with HTML5 and CSS3.
* **Real-Time Actuation & Feedback**:
  * **Open Action**: Rotates the servo motor to 90° (gate open), illuminates the Green LED, and turns off the Red LED.
  * **Close Action**: Rotates the servo motor back to 0° (gate closed), illuminates the Red LED, and turns off the Green LED.
* **Cross-Platform Compatibility**: Tested and verified virtually via **Wokwi Simulation** prior to physical deployment on hardware.

---

## Hardware Requirements

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **WeMos D1 Mini ESP32** | 1 | Microcontroller board |
| **Servo Motor** | 1 | Positional actuator for gate control |
| **Green LED** | 1 | Status indicator for "Open" |
| **Red LED** | 1 | Status indicator for "Closed" |
| **220Ω Resistors** | 2 | Current-limiting resistors for LEDs |
| **Breadboard & Jumper Wires** | As needed | Hardware interconnections |

---

## Circuit Schematic & Pin Mapping

> **Note**: Ensure the servo motor is powered via the **5V / VBUS** pin of the WeMos D1 Mini to provide adequate current during rotation.

| Component Pin | ESP32 Board Label | GPIO Mapping |
| :--- | :--- | :--- |
| **Servo Signal (Orange/Yellow)** | D18 | GPIO 18 |
| **Servo VCC (Red)** | 5V / VBUS | 5V |
| **Servo GND (Black)** | GND | GND |
| **Green LED (+ Anode via 220Ω)** | D2 | GPIO 2 |
| **Red LED (+ Anode via 220Ω)** | D4 | GPIO 4 |
| **LED Cathodes (-)** | GND | GND |

### The image below illustrates the connection using the Wokwi simulator & ESP32 .

<img width="715" height="491" alt="Screenshot 2026-08-05 165404" src="https://github.com/user-attachments/assets/4f92b829-9ad3-4d82-9d4a-3eeeeb24cc13" />

---

## Software Requirements & Libraries

* **Arduino IDE** (v2.0 or higher recommended)
* **ESP32 Board Package**: `esp32` by Espressif Systems
* **Libraries**: `ESP32Servo` *(Install via Arduino Library Manager)*

---

## How to Use

### 1. Connect to Wi-Fi

Open the Wi-Fi settings on your phone or computer and connect to:

```text
Network: ESP32_Control
Password: 12345678Password
```

### 2. Access the Control Panel

Open a web browser such as Chrome, Safari, or Firefox and navigate to:

```text
http://192.168.4.1
```

### 3. Control the Gate

Use the web control panel to operate the gate:

- Open — Moves the servo to 90° and turns on the green LED.
- Close — Moves the servo to 0° and turns on the red LED.

---

## Result

[Click here](https://drive.google.com/file/d/1kYc-BK10PMtaOhhRTrBGoMhBdif40hVS/view?usp=drive_link)

---


