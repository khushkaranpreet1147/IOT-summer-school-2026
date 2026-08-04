Project Title: LED Blink with Potentiometer Control
Hardware Required
Arduino Uno
LED
220-ohm resistor
Potentiometer
Breadboard and Jumper Wires
Circuit Diagram Description
Connect the LED's long leg to digital pin 13 via the 220-ohm resistor, and the short leg to GND.
Connect the potentiometer's outer pins to 5V and GND.
Connect the middle (wiper) pin of the potentiometer to analog pin A0.
How to Upload Code
Connect the Arduino board to your computer via USB.
Open the led_blink.ino file in the Arduino IDE.
Select the correct board (Arduino Uno) and port under the Tools menu.
Click the Upload button to transfer the code to your board.
Expected Output
The LED will blink at a rate determined by the potentiometer position. The current blink interval is displayed in the Serial Monitor.

Troubleshooting Tips
LED not lighting up: Ensure the LED is connected with the correct polarity (long leg is positive).
Code upload failure: Verify that the correct COM port is selected in the Tools menu.
Serial Monitor blank: Ensure the baud rate is set to 9600 in the bottom right corner of the Serial Monitor window.
