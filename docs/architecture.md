# System Architecture

## Overview

Smart Agro Rover consists of four major layers:

1. Hardware
2. ESP32 firmware
3. Communication/API
4. Web dashboard

```text
┌──────────────────────┐
│    Web Dashboard     │
└──────────┬───────────┘
           │ HTTP
           ▼
┌──────────────────────┐
│      ESP32           │
│   Web Server / API   │
└──────────┬───────────┘
           │
   ┌───────┼─────────┐
   │       │         │
   ▼       ▼         ▼
Sensors  Motors   Actuators
            │
            ├── Seed System
            ├── Water Pump
            └── Medicine Pump
```

## Communication

The initial version uses Wi-Fi and HTTP.

Future versions may use WebSocket communication for lower-latency real-time control and monitoring.
