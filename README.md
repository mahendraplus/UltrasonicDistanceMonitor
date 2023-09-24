# Ultrasonic Distance Monitor :chart_with_upwards_trend:

Monitor distances using an ultrasonic sensor and display the data on a web interface.

## Features :rocket:

- Real-time distance monitoring :chart_with_upwards_trend:
- Web-based user interface :globe_with_meridians:
- Servo motor control :robot_face:

## Demo :movie_camera:

![Demo](demo.gif)

## Wire Connections :electric_plug:

- **Ultrasonic Sensor**:
  - VCC -> 5V
  - Trig -> D1 (or your preferred trigger pin)
  - Echo -> D2 (or your preferred echo pin)
  - GND -> GND

- **Servo Motor**:
  - VCC -> 5V
  - Signal -> D4 (or your preferred servo signal pin)
  - GND -> GND

- **ESP8266**:
  - Ensure proper connections for power and ground.

## Setup :wrench:

1. Clone the repository:

```bash
git clone https://github.com/yourusername/ultrasonic-distance-monitor.git
cd ultrasonic-distance-monitor
