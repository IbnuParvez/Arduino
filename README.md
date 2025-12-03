Arduino Ultrasonic Distance Sensor with
 Bluetooth and LCD
 This project demonstrates how to use an Arduino to measure distance using an ultrasonic sensor, display
 the results on an I2C LCD, and send the data to a Bluetooth device. It also includes a buzzer for proximity
 alerts and the ability to receive and display messages from a Bluetooth-connected device. This project is
 ideal for IT students learning about microcontrollers, sensors, and wireless communication.
 Project Logic
 The core logic of the project revolves around the following steps:
 1. Distance Measurement: The Arduino triggers an ultrasonic sensor (HC-SR04)
 to send out a sound wave. The sensor then listens for the echo. The time
 difference between sending the pulse and receiving the echo is used to calculate
 the distance to an object.
 2. LCDDisplay: The calculated distance is displayed on a 16x2 I2C LCD. The top
 row shows the real-time distance, and the bottom row can display messages
 received via Bluetooth.
 3. Bluetooth Communication: A Bluetooth module (HC-06) is used to send the
 distance data to a connected device (e.g., a smartphone) and to receive
 messages from it. To avoid flooding the receiving device with data, the distance
 information is sent at a fixed interval (every 1 second).
 4. Proximity Alert: A buzzer is connected to the Arduino. If the measured distance
 is less than a certain threshold (50 cm in this code), the buzzer will sound,
 providing an audible warning.
 Libraries Used
 This project utilizes the following Arduino libraries:
 · Wire.h: This library allows you to communicate with I2C / TWI devices. It's used
 by the LiquidCrystal_I2C library to communicate with the LCD.
 · LiquidCrystal_I2C.h: This library is used to control I2C-based 16x2 LCDs. It
 simplifies the process of printing text and numbers to the screen.
 · SoftwareSerial.h: This library allows for serial communication on other digital
 pins of the Arduino, enabling you to connect a second serial device (like the
 Bluetooth module) while still using the main hardware serial for debugging.
 Core Functions
 The PROJECT.ino sketch is divided into two main functions: setup() and loop().
 setup()
 This function runs once when the Arduino is powered on or reset. It's used for initialization:
 · Initializes the I2C LCD and turns on the backlight.
· Setsupthe pin modes for the ultrasonic sensor's trigPin (OUTPUT) and
 echoPin (INPUT), and the buzzerPin (OUTPUT).
 · Starts serial communication with the Bluetooth module at a baud rate of 9600.
 · Displays a "System Active" message on the LCD for a second.
 loop()
 This function runs continuously after setup() has completed. It contains the main logic of the project:
 1. Triggers the Ultrasonic Sensor: It sends a short pulse to the trigPin of the
 ultrasonic sensor to start a measurement.
 2. Reads the Echo: It measures the duration of the pulse on the echoPin.
 3. Calculates Distance: It converts the pulse duration into distance in centimeters.
 4. Controls the Buzzer: It checks if the distance is less than 50 cm. If it is, the
 buzzer is turned on. Otherwise, it's turned off.
 5. Updates the LCD:
 o Thetoprow of the LCD is updated with the current distance.
 o It checks for incoming data from the Bluetooth module. If a new message
 is received, the bottom row of the LCD is updated with this message.
 6. Sends Data via Bluetooth: At a regular interval (1 second), it sends the distance
 and a warning message (if the distance is less than 50 cm) to the connected
 Bluetooth device.
 Hardware and Connections
 To build this project, you will need the following components:
 · Arduino Uno (or a similar board)
 · Ultrasonic Sensor (HC-SR04)
 · 16x2I2C LCD
 · Bluetooth Module (HC-05 or HC-06)
 · Buzzer
 · Breadboard and Jumper Wires


```markdown
 Wiring Diagram
 Here's how to connect the components to your Arduino:
 Component
 I2C LCD
 VCC
 GND
 SDA
 SCL
 Ultrasonic Sensor
 VCC
 GND
 Trig Pin
 Echo Pin
 Buzzer
 Positive (+)
 Arduino Pin
 5V
 GND
 A4 (SDA)
 A5 (SCL)
 5V
 GND
 Pin 9
 Pin 10
 Pin 11
other
 GND
 Bluetooth Module
 VCC
 GND
 TXD
 RXD
 5V
 GND
 Pin 0 (Arduino RX)
 Pin 1 (Arduino TX
 ```

 Important Note on Bluetooth Connection: The SoftwareSerial library is configured to use Pin 0
 (RX) and Pin 1 (TX) on the Arduino. This can conflict with the USB connection used for programming the
 Arduino. It's a good practice to disconnect the Bluetooth module's VCC or TX/RX pins while
 uploading the sketch to the Arduino.
 Howto Use
 1. Assemble the Circuit: Connect all the components as described in the wiring
 diagram.
 2. Upload the Code: Open the PROJECT.ino file in the Arduino IDE, select your
 board and port, and upload the sketch. Remember to disconnect the Bluetooth
 module's VCC or TX/RX pins during the upload.
 3. Power Up: Power the Arduino. The LCD should light up and display "System
 Active" and then start showing the distance.
 4. Connect via Bluetooth:
 o Onyoursmartphone or computer, search for Bluetooth devices. You
 should see a device named "HC-05" or "HC-06" (or whatever your module
 is named).
 o Pair with the device. The default PIN is usually "1234" or "0000".
 o UseaBluetooth serial terminal app (like "Serial Bluetooth Terminal" on
 Android) to connect to the paired device.
 5. View Data and Send Messages:
 o Youwill start seeing distance readings and warnings in the terminal app.
 o Youcantype a message in the terminal app and send it to the Arduino.
 The message will appear on the bottom row of the LCD
