Smart Home Automation System (Dual Microcontroller)
 This project implements a sophisticated Smart Home Automation system utilizing two interconnected microcontrollers (MCUs) to manage home environment parameters, offering control via both a local Keypad/LCD interface (Manual) and a remote Bluetooth interface.
 1. Core Hardware and Communication Protocols
 The project successfully integrates all three core serial communication protocols of the AVR microcontroller family:
 • MCU Communication (MCU-to-MCU): High-speed data exchange using the **SPI (Serial Peripheral Interface)** protocol.
 • Bluetooth Connectivity: Wireless control commands are received via the **UART (Universal Asynchronous Receiver/Transmitter)** protocol.
 • Configuration Storage: The system password is stored/retrieved from external non-volatile memory (EEPROM) using the **I2C (Inter-Integrated Circuit)** protocol.

 2. System Flow and Security
 The system initiates with a robust security check:
 2.1 Password Entry and LCD Display: User enters the password via Keypad.
 2.2 EEPROM Verification: Password is compared against the default password stored in **I2C EEPROM**.
 2.3 Security Breach Handling (Buzzer): If the password is entered incorrectly for 3 consecutive attempts, a **Buzzer** is activated and the system locks.

 3. Operation Modes and Control Features
 Upon successful login, the user selects between Manual (Keypad) control or Remote (Bluetooth/UART) control.
 Manual and Remote Control Menus The system provides two PWM control sub-menus:
 3.1 Lights (LEDs) Menu: Allows the user to control the light brightness using **PWM (Pulse Width Modulation)**, enabling adjustable dimming levels.
 3.2 Fans (Motors) Menu: Allows the user to manually control the **ON/OFF status** and **speed** (Low/Medium/High) of the cooling fans, also via PWM.
 
 4 Environmental Sensing and Automatic Control
 The system utilizes sensors for autonomous environmental management:
 4.1 Temperature Sensor: Reads the current room temperature.
 4.2 Smoke Sensor: Monitors for potential fire or smoke hazards.
 4.3 AutomaticFanSpeedAdjustment: Basedontemperaturereadings, thesystemautomatically adjusts the fan speed using **PWM**.
 4.4 Emergency Fire Alert: If the Smoke Sensor detects a dangerous level of smoke:
 • The **Buzzer** is immediately triggered.
 • Awarning message (e.g., ”Wel3aaa!”) is printed on the LCD screen.
