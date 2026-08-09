```python
import requests
import sys


ROVER_IP = "192.168.1.100"


def get_status():

    url = f"http://{ROVER_IP}/api/status"

    try:

        response = requests.get(
            url,
            timeout=3
        )

        response.raise_for_status()

        print(response.json())

    except requests.RequestException as error:

        print(
            f"Connection failed: {error}"
        )


def send_command(command):

    url = (
        f"http://{ROVER_IP}"
        f"/api/command"
    )

    try:

        response = requests.get(
            url,
            params={
                "cmd": command
            },
            timeout=3
        )

        response.raise_for_status()

        print(response.json())

    except requests.RequestException as error:

        print(
            f"Command failed: {error}"
        )


if __name__ == "__main__":

    if len(sys.argv) < 2:

        print(
            "Usage:"
        )

        print(
            "python api_test.py status"
        )

        print(
            "python api_test.py forward"
        )

        print(
            "python api_test.py stop"
        )

        sys.exit(1)


    command = sys.argv[1]

    if command == "status":

        get_status()

    else:

        send_command(command)
```
