# Software Documentation

## Firmware

The ESP32 firmware is responsible for:

* Wi-Fi connectivity
* Web server
* Motor control
* Sensor reading
* Seed dispensing
* Water pump control
* Medicine pump control
* Automatic irrigation
* Rover safety

## Dashboard

The dashboard provides:

* Rover movement control
* Agricultural operation control
* Sensor monitoring
* Operating mode selection
* Connection status

## API

The API provides communication between the dashboard and ESP32.

Current API:

```text
GET /api/status
GET /api/command?cmd=COMMAND
```

## Future Software

* WebSocket communication
* Database logging
* User authentication
* Cloud dashboard
* Mobile application
* OTA firmware updates
* Autonomous navigation
