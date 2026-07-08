​Problem Statement
A J&K horticulture farmer wants to automate irrigation for a small saffron farm plot. The system should read soil moisture every 30 minutes and activate a water pump only when the soil is dry. Saffron is sensitive to overwatering — the system must also prevent watering if it rained recently (use LDR to detect low light/overcast sky as a rain proxy and also leverage the use of api also). The farmer must be able to manually override via a button.

📌 Project Overview
​This project automates the watering process for small saffron plots. By integrating soil moisture monitoring, light-level analysis (to detect rain/overcast conditions), and cloud logging, the system ensures optimal hydration while preventing crop damage from excessive water.


​🛠 Features
Intelligent Logic: Automatically checks soil moisture every 30 minutes; skips irrigation if ambient light suggests rain/overcast conditions.
​Cloud Logging: Logs status updates (Moisture %, Mode, Last Watered Time) to a Google Sheet via ESP8266 and IFTTT/Google Scripts.
​Manual Override: Physical push button for manual pump activation with an automatic 5-minute safety lockout.
​Local Monitoring: Real-time system status displayed on a 16x2 I2C LCD.

​💻 Hardware Requirements
​Microcontroller: ESP8266 (NodeMCU)
​Sensors: Soil Moisture Sensor, LDR Module
​Actuators: Relay Module (to control pump/LED)
​Interface: 16x2 LCD with I2C module, Push Button
​Connectivity: Wi-Fi (for API calls and Google Sheets logging)

​🏗 Circuit Diagram

​🚀 Development Progress (Git Log)
​This project follows a modular development cycle:
​Initial Setup: Core sensor integration and basic I/O testing.
​Display & Relay: Integration of I2C LCD and pump simulation.
​Override Logic: Implementation of manual button and millis()-based lockout.
​API/IoT: Cloud connectivity via HTTP requests.
​Refactoring: Final stabilization of the main automation loop.
​
