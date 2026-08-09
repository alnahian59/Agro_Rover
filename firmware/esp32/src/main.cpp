```cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// ============================================================
// SMART AGRO ROVER
// ESP32 Main Firmware
// ============================================================

// -------------------- Wi-Fi Configuration --------------------

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// -------------------- Motor Pins -----------------------------

#define MOTOR_LEFT_IN1   26
#define MOTOR_LEFT_IN2   27
#define MOTOR_RIGHT_IN1  14
#define MOTOR_RIGHT_IN2  12

#define MOTOR_LEFT_EN    25
#define MOTOR_RIGHT_EN   13

// -------------------- Sensor Pins ----------------------------

#define SOIL_MOISTURE_PIN 34
#define ULTRASONIC_TRIG  5
#define ULTRASONIC_ECHO  18

// -------------------- Actuator Pins --------------------------

#define SEED_SERVO_PIN    19
#define WATER_PUMP_PIN    23
#define MEDICINE_PUMP_PIN 22

// -------------------- Status ---------------------------------

bool waterPumpState = false;
bool medicinePumpState = false;
bool automaticMode = false;

int soilMoisture = 0;
float distanceCM = 0;

Servo seedServo;

WebServer server(80);

// ============================================================
// MOTOR CONTROL
// ============================================================

void stopMotors() {
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void moveForward() {
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, LOW);

    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void moveBackward() {
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);

    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}

void turnLeft() {
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);

    digitalWrite(MOTOR_RIGHT_IN1, HIGH);
    digitalWrite(MOTOR_RIGHT_IN2, LOW);
}

void turnRight() {
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, LOW);

    digitalWrite(MOTOR_RIGHT_IN1, LOW);
    digitalWrite(MOTOR_RIGHT_IN2, HIGH);
}

// ============================================================
// SEED SYSTEM
// ============================================================

void releaseSeed() {
    seedServo.write(90);
    delay(400);

    seedServo.write(0);
    delay(400);

    seedServo.write(45);
}

// ============================================================
// WATER SYSTEM
// ============================================================

void setWaterPump(bool state) {
    waterPumpState = state;
    digitalWrite(WATER_PUMP_PIN, state ? HIGH : LOW);
}

// ============================================================
// MEDICINE SYSTEM
// ============================================================

void setMedicinePump(bool state) {
    medicinePumpState = state;
    digitalWrite(MEDICINE_PUMP_PIN, state ? HIGH : LOW);
}

// ============================================================
// ULTRASONIC SENSOR
// ============================================================

float readDistance() {

    digitalWrite(ULTRASONIC_TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(ULTRASONIC_TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(ULTRASONIC_TRIG, LOW);

    long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000);

    if (duration == 0) {
        return -1;
    }

    return duration * 0.0343 / 2.0;
}

// ============================================================
// SENSOR UPDATE
// ============================================================

void updateSensors() {

    int rawMoisture = analogRead(SOIL_MOISTURE_PIN);

    soilMoisture = map(
        rawMoisture,
        4095,
        0,
        0,
        100
    );

    soilMoisture = constrain(
        soilMoisture,
        0,
        100
    );

    distanceCM = readDistance();
}

// ============================================================
// JSON STATUS
// ============================================================

String getStatusJSON() {

    updateSensors();

    JsonDocument doc;

    doc["status"] = "online";
    doc["mode"] = automaticMode ? "automatic" : "manual";

    doc["soilMoisture"] = soilMoisture;
    doc["distance"] = distanceCM;

    doc["waterPump"] = waterPumpState;
    doc["medicinePump"] = medicinePumpState;

    doc["seedSystem"] = "ready";

    String output;

    serializeJson(doc, output);

    return output;
}

// ============================================================
// API
// ============================================================

void handleStatus() {

    server.send(
        200,
        "application/json",
        getStatusJSON()
    );
}

void handleCommand() {

    if (!server.hasArg("cmd")) {
        server.send(
            400,
            "application/json",
            "{\"error\":\"Missing command\"}"
        );

        return;
    }

    String command = server.arg("cmd");

    if (command == "forward") {
        moveForward();
    }

    else if (command == "backward") {
        moveBackward();
    }

    else if (command == "left") {
        turnLeft();
    }

    else if (command == "right") {
        turnRight();
    }

    else if (command == "stop") {
        stopMotors();
    }

    else if (command == "seed") {
        releaseSeed();
    }

    else if (command == "water_on") {
        setWaterPump(true);
    }

    else if (command == "water_off") {
        setWaterPump(false);
    }

    else if (command == "medicine_on") {
        setMedicinePump(true);
    }

    else if (command == "medicine_off") {
        setMedicinePump(false);
    }

    else if (command == "auto") {
        automaticMode = true;
    }

    else if (command == "manual") {
        automaticMode = false;
    }

    else {
        server.send(
            400,
            "application/json",
            "{\"error\":\"Unknown command\"}"
        );

        return;
    }

    server.send(
        200,
        "application/json",
        "{\"success\":true}"
    );
}

// ============================================================
// ROOT
// ============================================================

void handleRoot() {

    server.send(
        200,
        "text/plain",
        "Smart Agro Rover ESP32 Server"
    );
}

// ============================================================
// SETUP
// ============================================================

void setup() {

    Serial.begin(115200);

    // Motor pins
    pinMode(MOTOR_LEFT_IN1, OUTPUT);
    pinMode(MOTOR_LEFT_IN2, OUTPUT);
    pinMode(MOTOR_RIGHT_IN1, OUTPUT);
    pinMode(MOTOR_RIGHT_IN2, OUTPUT);

    pinMode(MOTOR_LEFT_EN, OUTPUT);
    pinMode(MOTOR_RIGHT_EN, OUTPUT);

    // Sensors
    pinMode(SOIL_MOISTURE_PIN, INPUT);

    pinMode(
        ULTRASONIC_TRIG,
        OUTPUT
    );

    pinMode(
        ULTRASONIC_ECHO,
        INPUT
    );

    // Pumps
    pinMode(
        WATER_PUMP_PIN,
        OUTPUT
    );

    pinMode(
        MEDICINE_PUMP_PIN,
        OUTPUT
    );

    // Default state
    stopMotors();

    setWaterPump(false);
    setMedicinePump(false);

    // Servo
    seedServo.attach(SEED_SERVO_PIN);

    seedServo.write(45);

    // Wi-Fi
    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );

    Serial.print("Connecting to Wi-Fi");

    while (
        WiFi.status() != WL_CONNECTED
    ) {

        delay(500);

        Serial.print(".");
    }

    Serial.println();

    Serial.println(
        "Wi-Fi connected"
    );

    Serial.print(
        "Rover IP: "
    );

    Serial.println(
        WiFi.localIP()
    );

    // Web server
    server.on(
        "/",
        handleRoot
    );

    server.on(
        "/api/status",
        handleStatus
    );

    server.on(
        "/api/command",
        handleCommand
    );

    server.begin();

    Serial.println(
        "Smart Agro Rover server started"
    );
}

// ============================================================
// LOOP
// ============================================================

void loop() {

    server.handleClient();

    // Basic automatic irrigation
    if (automaticMode) {

        updateSensors();

        if (soilMoisture < 35) {
            setWaterPump(true);
        }

        else if (soilMoisture > 50) {
            setWaterPump(false);
        }
    }

    delay(10);
}
```
