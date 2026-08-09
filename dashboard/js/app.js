```javascript
// ============================================================
// SMART AGRO ROVER
// Dashboard Application
// ============================================================

// If dashboard is served directly by ESP32,
// leave this empty.
//
// If dashboard is hosted somewhere else,
// set this to the ESP32 IP address.
//
// Example:
// const ROVER_IP = "192.168.1.100";

const ROVER_IP = "";


// ============================================================
// API URL
// ============================================================

function apiURL(endpoint) {

    if (ROVER_IP === "") {
        return endpoint;
    }

    return `http://${ROVER_IP}${endpoint}`;
}


// ============================================================
// SEND COMMAND
// ============================================================

async function sendCommand(command) {

    try {

        const response = await fetch(
            apiURL(
                `/api/command?cmd=${command}`
            )
        );

        const data =
            await response.json();

        console.log(
            "Command:",
            command,
            data
        );

        updateStatus();

    }

    catch (error) {

        console.error(
            "Command failed:",
            error
        );

        setOffline();

    }
}


// ============================================================
// GET STATUS
// ============================================================

async function updateStatus() {

    try {

        const response =
            await fetch(
                apiURL("/api/status"),
                {
                    cache: "no-store"
                }
            );

        if (!response.ok) {
            throw new Error(
                "Server unavailable"
            );
        }

        const data =
            await response.json();

        updateDashboard(data);

        setOnline();

    }

    catch (error) {

        console.error(
            "Status error:",
            error
        );

        setOffline();

    }
}


// ============================================================
// UPDATE DASHBOARD
// ============================================================

function updateDashboard(data) {

    document.getElementById(
        "soilMoisture"
    ).textContent =
        `${data.soilMoisture ?? "--"} %`;


    document.getElementById(
        "distance"
    ).textContent =
        `${data.distance ?? "--"} cm`;


    document.getElementById(
        "mode"
    ).textContent =
        (
            data.mode || "manual"
        ).toUpperCase();


    document.getElementById(
        "waterPump"
    ).textContent =
        data.waterPump
            ? "ON"
            : "OFF";


    document.getElementById(
        "medicinePump"
    ).textContent =
        data.medicinePump
            ? "ON"
            : "OFF";


    document.getElementById(
        "seedSystem"
    ).textContent =
        (
            data.seedSystem ||
            "READY"
        ).toUpperCase();

}


// ============================================================
// ONLINE STATUS
// ============================================================

function setOnline() {

    const element =
        document.getElementById(
            "connectionStatus"
        );

    element.textContent =
        "● ONLINE";

    element.classList.remove(
        "offline"
    );

    element.classList.add(
        "online"
    );
}


// ============================================================
// OFFLINE STATUS
// ============================================================

function setOffline() {

    const element =
        document.getElementById(
            "connectionStatus"
        );

    element.textContent =
        "● OFFLINE";

    element.classList.remove(
        "online"
    );

    element.classList.add(
        "offline"
    );
}


// ============================================================
// AUTO REFRESH
// ============================================================

setInterval(
    updateStatus,
    1000
);


// Initial status request

updateStatus();
```
