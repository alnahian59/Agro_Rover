# 🌱 Agro Rover

An ESP32-based agricultural rover designed to automate essential farming operations such as **seed sowing, water irrigation, and agricultural medicine/pesticide distribution**.

The rover can be controlled and monitored through a **web-based dashboard**, allowing the operator to control movement, manage agricultural operations, and monitor important sensor data in real time.

---

## 🚜 Project Overview

Modern agriculture increasingly requires automation to improve productivity, reduce labor requirements, and use agricultural resources efficiently.

**Agro Rover** is a multifunctional agricultural robotic platform designed to assist farmers with common agricultural tasks.

The rover combines:

* 🤖 Mobile robotic platform
* 🌱 Automatic seed sowing
* 💧 Water distribution
* 🧪 Agricultural medicine/pesticide distribution
* 🌡️ Environmental monitoring
* 📡 Wireless communication
* 🌐 Web-based control dashboard
* 📊 Real-time rover monitoring
* ⚡ Battery/Power monitoring
* 🛞 Motorized movement system

The main controller of the rover is an **ESP32**, which provides Wi-Fi connectivity, sensor interfacing, actuator control, and web-server functionality.

---

## 🎯 Objectives

The main objectives of this project are:

1. Develop a multifunctional agricultural rover.
2. Automate seed sowing operations.
3. Automate water distribution for crops.
4. Provide agricultural medicine/pesticide distribution.
5. Enable wireless rover control.
6. Develop a real-time web dashboard.
7. Monitor rover sensors remotely.
8. Reduce manual agricultural workload.
9. Improve resource efficiency.
10. Create an extensible platform for future agricultural automation.

---

## ✨ Main Features

### 🛞 Rover Movement

The rover supports remote movement control through the web dashboard.

Available controls include:

* Forward
* Reverse
* Left
* Right
* Stop

The movement system is controlled using motor drivers connected to the ESP32.

---

### 🌱 Seed Sowing System

The seed distribution mechanism is designed to automatically release seeds while the rover moves.

Possible features include:

* Controlled seed release
* Adjustable seed dispensing interval
* Seed hopper
* Servo/DC motor-based dispensing mechanism
* Manual control from dashboard
* Automatic sowing mode

The system can be further developed to support configurable spacing between seeds.

---

### 💧 Water Distribution System

The rover contains a water storage tank and pump system for irrigation.

The water system can be controlled through the dashboard.

Possible operating modes:

* Manual watering
* Automatic watering
* Timed watering
* Sensor-based watering

The system can use soil moisture data to determine whether irrigation is required.

---

### 🧪 Agricultural Medicine Distribution

A separate tank and pump mechanism can be used for agricultural medicine or pesticide distribution.

The dashboard can provide controls for:

* Medicine pump ON/OFF
* Spray duration
* Manual spraying
* Automatic spraying
* Tank status monitoring

> **Safety note:** The prototype should initially be tested using water or another safe substitute. Real pesticides/chemicals should only be used with appropriate agricultural and safety procedures.

---

## 🌐 Web-Based Dashboard

The rover provides a web-based dashboard for controlling and monitoring the system.

The dashboard can display:

### Rover Status

* Connection status
* Rover mode
* Motor status
* Battery level
* System uptime

### Environmental Data

* Temperature
* Humidity
* Soil moisture
* Optional light intensity

### Agricultural Operations

* Seed dispenser status
* Water pump status
* Medicine pump status
* Operation duration
* Automatic/manual mode

### Rover Controls

```text
        FORWARD
           ▲
           │
     ◀── LEFT  RIGHT ──▶
           │
           ▼
        REVERSE

          STOP
```

---

## 🧠 System Architecture

```text
                    ┌──────────────────────┐
                    │    Web Dashboard     │
                    │                      │
                    │  Control + Monitor   │
                    └──────────┬───────────┘
                               │
                            Wi-Fi
                               │
                               ▼
                    ┌──────────────────────┐
                    │        ESP32         │
                    │                      │
                    │  Web Server          │
                    │  Control Logic       │
                    │  Sensor Processing   │
                    └──────────┬───────────┘
                               │
          ┌────────────────────┼────────────────────┐
          │                    │                    │
          ▼                    ▼                    ▼
   ┌─────────────┐      ┌─────────────┐     ┌──────────────┐
   │ Motor Driver│      │   Sensors   │     │  Actuators   │
   └──────┬──────┘      └──────┬──────┘     └───────┬──────┘
          │                    │                    │
          ▼                    ▼                    ▼
       Motors             Environment        Pumps / Servo
                              │
                    ┌─────────┴─────────┐
                    │                   │
               Soil Moisture      Temp/Humidity
```

---

# 🔧 Hardware

The exact hardware configuration may change during development.

A typical system can contain:

### Controller

* ESP32 development board

### Motor System

* DC geared motors
* Motor driver
* Wheels
* Caster wheel

### Agricultural System

* Seed hopper
* Seed dispensing mechanism
* Water tank
* Water pump
* Spray/medicine tank
* Spray pump
* Nozzle
* Servo motor or geared motor

### Sensors

* Soil moisture sensor
* Temperature and humidity sensor
* Ultrasonic sensor
* Battery voltage sensor

Optional:

* GPS module
* IMU
* Rain sensor
* Light sensor
* Camera
* Current sensor

### Power

* Rechargeable battery
* Buck converter
* Power distribution system
* Main power switch
* Fuse/protection system

---

# 📦 Hardware Block Diagram

```text
                    BATTERY
                       │
                       ▼
              ┌─────────────────┐
              │ Power Management │
              └────────┬────────┘
                       │
             ┌─────────┴─────────┐
             │                   │
             ▼                   ▼
           ESP32             Motor Driver
             │                   │
     ┌───────┼────────┐          ▼
     │       │        │       DC Motors
     ▼       ▼        ▼
 Sensors  Servo     Pumps
     │       │        │
     ▼       ▼        ├─────────────┐
 Soil      Seed      │             │
Moisture  Dispenser  ▼             ▼
                 Water Pump    Spray Pump
```

---

# 💻 Software Architecture

The software is divided into several components.

```text
ESP32 Firmware
       │
       ├── Wi-Fi Manager
       ├── Web Server
       ├── Motor Controller
       ├── Seed Controller
       ├── Water Controller
       ├── Medicine Controller
       ├── Sensor Manager
       └── System Monitor
                │
                ▼
          Web Dashboard
                │
       ┌────────┴────────┐
       ▼                 ▼
   Controls          Monitoring
```

---

# 📁 Repository Structure

```text
SmartAgroRover/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── docs/
│   ├── architecture.md
│   ├── hardware.md
│   ├── software.md
│   ├── dashboard.md
│   └── wiring.md
│
├── firmware/
│   └── esp32/
│       ├── src/
│       │   └── main.cpp
│       ├── include/
│       ├── lib/
│       └── platformio.ini
│
├── dashboard/
│   ├── index.html
│   ├── css/
│   │   └── style.css
│   ├── js/
│   │   └── app.js
│   └── assets/
│
├── hardware/
│   ├── schematics/
│   ├── pcb/
│   ├── cad/
│   └── components.md
│
├── software/
│   ├── api/
│   └── tools/
│
├── images/
│
└── tests/
```

---

# 🚀 Getting Started

## 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/SmartAgroRover.git
```

Enter the project directory:

```bash
cd SmartAgroRover
```

---

## 2. Install Development Tools

Recommended tools:

* Visual Studio Code
* PlatformIO
* Arduino IDE
* Git
* ESP32 Board Package

---

## 3. Configure ESP32

Connect the ESP32 to your computer and select the correct board and serial port.

Configure Wi-Fi credentials in the firmware.

Example:

```cpp
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

---

## 4. Upload Firmware

Build and upload the ESP32 firmware.

After uploading, open the serial monitor and check the assigned IP address.

Example:

```text
Smart Agro Rover
WiFi Connected
IP Address: 192.168.1.100
Web Server Started
```

Open the displayed IP address in a browser.

---

# 🖥️ Dashboard

The dashboard is designed to provide a centralized interface for operating the rover.

Example dashboard sections:

```text
┌──────────────────────────────────────────────┐
│              SMART AGRO ROVER                │
├──────────────────────────────────────────────┤
│ Connection: 🟢 ONLINE                       │
│ Battery:  ████████░░ 82%                    │
├──────────────────────────────────────────────┤
│              ROVER CONTROL                   │
│                                              │
│                  ▲                           │
│                Forward                       │
│          ◀ Left     Stop     Right ▶         │
│                  ▼                           │
│                Reverse                       │
├──────────────────────────────────────────────┤
│ AGRICULTURAL OPERATIONS                     │
│                                              │
│ 🌱 Seed      [ ON / OFF ]                   │
│ 💧 Water     [ ON / OFF ]                   │
│ 🧪 Medicine  [ ON / OFF ]                   │
├──────────────────────────────────────────────┤
│ SENSOR MONITORING                           │
│                                              │
│ Temperature:      -- °C                     │
│ Humidity:         -- %                      │
│ Soil Moisture:    -- %                      │
│ Battery Voltage:  -- V                      │
└──────────────────────────────────────────────┘
```

---

# 📊 Monitoring

The system can monitor:

| Parameter       | Purpose                           |
| --------------- | --------------------------------- |
| Soil Moisture   | Determine irrigation requirement  |
| Temperature     | Environmental monitoring          |
| Humidity        | Environmental monitoring          |
| Battery Voltage | Power monitoring                  |
| Distance        | Obstacle detection                |
| Motor Status    | Rover diagnostics                 |
| Pump Status     | Agricultural operation monitoring |
| Seed Status     | Seed dispensing monitoring        |

---

# 🔄 Operating Modes

## Manual Mode

The operator directly controls the rover.

```text
Dashboard
    ↓
User Command
    ↓
ESP32
    ↓
Motor / Pump / Servo
```

---

## Automatic Mode

The rover performs agricultural operations according to predefined conditions.

Example:

```text
Soil Moisture
      ↓
Check Threshold
      ↓
Moisture LOW?
   ┌──┴──┐
  YES    NO
   │      │
   ▼      ▼
Pump ON  Pump OFF
```

---

# 🔐 Safety Considerations

The rover should include appropriate safety mechanisms.

Recommended features:

* Emergency stop
* Motor stop on communication loss
* Pump timeout
* Low-battery protection
* Obstacle detection
* Manual override
* Electrical fuse/protection
* Separate power management for motors and electronics

For agricultural chemical spraying, use appropriate protective equipment and follow the chemical manufacturer's instructions and applicable local regulations.

---

# 🧪 Testing

Testing should be performed in stages.

### Stage 1 — Motor Test

Verify:

* Forward
* Reverse
* Left
* Right
* Stop

### Stage 2 — Sensor Test

Verify:

* Soil moisture
* Temperature
* Humidity
* Distance
* Battery voltage

### Stage 3 — Pump Test

Test:

* Water pump
* Spray pump
* Pump control
* Automatic shutoff

### Stage 4 — Seed System

Test:

* Seed dispensing
* Dispensing interval
* Servo/motor mechanism

### Stage 5 — Dashboard

Test:

* Web connection
* Movement controls
* Sensor updates
* Pump controls
* System status

### Stage 6 — Full Rover

Perform integrated field testing.

---

# 🛠️ Future Improvements

Planned future features include:

* [ ] Autonomous navigation
* [ ] GPS-based navigation
* [ ] Path planning
* [ ] Obstacle avoidance
* [ ] Camera-based crop monitoring
* [ ] AI-based plant disease detection
* [ ] Automatic weed detection
* [ ] Precision seed placement
* [ ] Variable-rate spraying
* [ ] Cloud monitoring
* [ ] Mobile application
* [ ] Data logging
* [ ] Field mapping
* [ ] Solar charging
* [ ] Remote emergency stop
* [ ] OTA firmware updates

---

# 🌍 Applications

The Smart Agro Rover can potentially be used for:

* Crop fields
* Vegetable farms
* Agricultural research
* Greenhouses
* Experimental farms
* Small-scale farming
* Precision agriculture research

---

# 📸 Project Images

Project images and development progress will be added here.

```text
/images
```

Recommended images:

* Complete rover
* Electronics
* Seed mechanism
* Water system
* Spray system
* Dashboard
* Wiring
* Field testing

---

# 🤝 Contributing

Contributions and suggestions are welcome.

To contribute:

```bash
git clone https://github.com/YOUR_USERNAME/SmartAgroRover.git
```

Create a new branch:

```bash
git checkout -b feature/your-feature
```

Make your changes and commit:

```bash
git add .
git commit -m "Add your feature"
```

Push the branch:

```bash
git push origin feature/your-feature
```

Then create a Pull Request.

---

# 📜 License

This project is licensed under the MIT License.

See the `LICENSE` file for details.

---

# 👨‍💻 Project Author

**Al Nahian Niloy**

GitHub:

https://github.com/YOUR_USERNAME

---

# ⭐ Support

If you find this project useful, consider giving the repository a ⭐ on GitHub.

---

## 📌 Project Status

**Status:** 🚧 Under Development

The Smart Agro Rover is currently under active development. Hardware, firmware, dashboard, and autonomous features are being developed and tested progressively.

---

## 🌱 Vision

The long-term goal of Smart Agro Rover is to develop an affordable and extensible agricultural robotic platform capable of performing repetitive farming operations autonomously while providing farmers with real-time monitoring and control.

**Automate agriculture. Reduce effort. Improve precision. 🌱🤖**
