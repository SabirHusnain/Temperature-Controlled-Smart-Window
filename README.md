# Arduino-based Temperature Controlled Smart Windows

This project focuses on the development of an Arduino-based temperature controlled smart windows system. The system utilizes reflectors controlled by servo motors to adjust the angle and control the temperature of the room. The project includes both software and hardware components to achieve temperature regulation.

## Description

The smart windows system consists of the following key components:

1. Arduino Nano: The Arduino Nano serves as the main controller for the system, responsible for reading temperature data, controlling the servo motors, and managing the overall functionality of the system.

2. DHT Sensors: Two DHT sensors (DHT22 for room temperature and DHT11 for ambient temperature) are used to measure the temperature values of the room and the surrounding environment.

3. Servo Motors: Servo motors are utilized to control the angle of the reflectors. By adjusting the angle, the system can regulate the amount of sunlight and heat entering the room.

4. Keypad and LCD Display: A keypad and an LCD display are incorporated to provide user interaction and display important system information such as current temperature, set temperature, error, and servo motor angle.

## Functionality

The Arduino-based temperature controlled smart windows system operates in two modes:

1. Auto Control: In auto mode, the system automatically adjusts the angle of the reflectors based on the temperature readings. If the current room temperature is higher than the ambient temperature, the system operates in winter mode, adjusting the angle to minimize heat gain. Conversely, if the current room temperature is lower than the ambient temperature, the system operates in summer mode, adjusting the angle to allow more heat to enter the room.

2. Manual Control: In manual mode, the user has the flexibility to set a specific angle for the servo motors using the keypad. This mode allows for precise control over the angle of the reflectors, regardless of the temperature differentials.

## Usage

1. Setup: Connect the DHT sensors, servo motors, keypad, and LCD display to the Arduino Nano following the provided pin configurations.

2. Upload Code: Upload the provided Arduino code to the Arduino Nano using the Arduino IDE.

3. Operation:
   - In auto mode: The system will automatically adjust the reflector angle based on the temperature differentials. No user intervention is required.
   - In manual mode: Use the keypad to enter the desired angle for the servo motors. The system will maintain that angle until manually changed.

## Applications

The Arduino-based temperature controlled smart windows system offers a range of potential applications, including:

- Energy-efficient building management: The system can help optimize energy consumption by regulating the amount of heat entering the room, reducing the need for artificial cooling or heating.
- Comfort and climate control: By adjusting the reflector angle, the system can maintain a comfortable temperature within the room, enhancing occupant comfort.
- Greenhouse temperature regulation: The system can be adapted for greenhouse applications, controlling the amount of sunlight and heat to create optimal growing conditions for plants.

The provided Arduino code and hardware setup serve as a foundation for implementing a reliable and efficient temperature control solution for smart windows.

For detailed instructions on setup, usage, and customization, please refer to the documentation included in the project repository.
