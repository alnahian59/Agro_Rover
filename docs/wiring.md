# Wiring Documentation

## ESP32 Pin Assignment

| Component          | ESP32 Pin |
| ------------------ | --------: |
| Left Motor IN1     |   GPIO 26 |
| Left Motor IN2     |   GPIO 27 |
| Right Motor IN1    |   GPIO 14 |
| Right Motor IN2    |   GPIO 12 |
| Left Motor Enable  |   GPIO 25 |
| Right Motor Enable |   GPIO 13 |
| Soil Moisture      |   GPIO 34 |
| Ultrasonic TRIG    |    GPIO 5 |
| Ultrasonic ECHO    |   GPIO 18 |
| Seed Servo         |   GPIO 19 |
| Water Pump         |   GPIO 23 |
| Medicine Pump      |   GPIO 22 |

## Important

Do not power motors or pumps directly from ESP32 GPIO pins.

Use appropriate motor drivers, MOSFETs, relays, or pump drivers.

All components must have appropriate power regulation and protection.

The final pin assignment should be updated whenever the hardware design changes.
