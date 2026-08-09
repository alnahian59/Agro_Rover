# Smart Agro Rover API

This directory contains the software API layer for communicating with the Smart Agro Rover.

The ESP32 currently exposes a REST-style HTTP API.

## Endpoints

### Get Rover Status

```text
GET /api/status
```

Example:

```json
{
    "status": "online",
    "mode": "manual",
    "soilMoisture": 62,
    "distance": 45.3,
    "waterPump": false,
    "medicinePump": false,
    "seedSystem": "ready"
}
```

---

## Send Rover Command

```text
GET /api/command?cmd=COMMAND
```

### Movement

```text
/api/command?cmd=forward
/api/command?cmd=backward
/api/command?cmd=left
/api/command?cmd=right
/api/command?cmd=stop
```

### Agriculture

```text
/api/command?cmd=seed

/api/command?cmd=water_on
/api/command?cmd=water_off

/api/command?cmd=medicine_on
/api/command?cmd=medicine_off
```

### Operating Modes

```text
/api/command?cmd=manual
/api/command?cmd=auto
```

---

## Future API

The API can later be expanded with:

```text
GET  /api/status
GET  /api/sensors
POST /api/motor
POST /api/seed
POST /api/water
POST /api/medicine
POST /api/mode
GET  /api/system
GET  /api/battery
```

WebSocket support can also be added for real-time communication.

```
```
