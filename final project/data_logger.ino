#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
String GOOGLE_SCRIPT_URL="google sheet link";
#define BUZZER_PIN 26
#define TEMP_THRESHOLD 18
#define HUM_THRESHOLD 30
#define GREEN_LED 25 //good
#define YELLOW_LED 33 //fair
#define RED_LED 32 //poor
#define BUTTON_PIN 14
const char* ssid="wifi name";
const char* password="password";
unsigned long channelID=your channel id;
const char *writeAPIKey="api key";
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
void connectWiFi();
bool buzzerMuted = false;
unsigned long muteTime = 0;
const unsigned long MUTE_DURATION = 30000; 
void setup(){
  Serial.begin(115200);
  dht.begin();
  delay(2000);
  connectWiFi();
  //BUZZER
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  ThingSpeak.begin(client);
  //OLED 
  Wire.begin(21,22); //SDA  --------> GPIO 21 SCL  --------> GPIO 22
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("OLED not found");
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,25);
  display.println("Warehouse Logger");
  display.display();
  delay(2000);
  Serial.println("System Ready");
  //LED INITIALIZING
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);//button
}
void loop(){
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi Lost...");
    connectWiFi();
  }
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int warehousehealth = calculatehealth(temperature, humidity);
  if (digitalRead(BUTTON_PIN) == LOW){
    buzzerMuted = true;
    muteTime = millis();
    digitalWrite(BUZZER_PIN, LOW);
    //Serial.println("Alarm Muted");
}
updateLEDs(warehousehealth);
  if (isnan(temperature) || isnan(humidity)){
    Serial.println("Failed to read DHT11!");
    delay(2000);
    return;
  }
  String healthstatus;
  if (warehousehealth >= 90)
    healthstatus = "Excellent";
  else if (warehousehealth >= 75)
    healthstatus = "Good";
  else if (warehousehealth >= 60)
    healthstatus = "Fair";
  else if (warehousehealth >= 40)
    healthstatus = "Poor";
  else
    healthstatus = "Critical";
  Serial.println("------------------------");
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity    : ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Warehouse Health: ");
  Serial.print(warehousehealth);
  Serial.println("%");
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, warehousehealth);
  HTTPClient http;
String status = "Normal";
if (temperature > 30 || humidity > 70){
    status = "Warning";
}
  bool alert = false;
if (temperature > TEMP_THRESHOLD){
  Serial.println("WARNING: High Temperature!");
  alert = true;
}
if (humidity > HUM_THRESHOLD){
  Serial.println("WARNING: High Humidity!");
  alert = true;
}
if(!alert){
    digitalWrite(BUZZER_PIN, LOW);
    // Reset mute
    buzzerMuted = false;
}
else{
    // Warehouse unhealthy
    if(buzzerMuted){
        // Check whether mute period is over
        if(millis() - muteTime >= MUTE_DURATION){
            buzzerMuted = false;
        }
    }
    if(!buzzerMuted){
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else{
        digitalWrite(BUZZER_PIN, LOW);
    }
}
String url = GOOGLE_SCRIPT_URL +"?temp=" + String(temperature) +"&hum=" + String(humidity) +"&status=" + status;
http.begin(url);
int httpCode = http.GET();
Serial.print("Google Sheets HTTP Code: ");
Serial.println(httpCode);
http.end();
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (response == 200){
    Serial.println("Data uploaded successfully.");
  }
  else{
    Serial.print("Upload failed. Error Code: ");
    Serial.println(response);
  }
  Serial.println();
bool cloudStatus = false;
//int response = ThingSpeak.writeFields(channelID, writeAPIKey);
if(response == 200){
    cloudStatus = true;
}
else{
    cloudStatus = false;
}
updateOLED(
    temperature,
    humidity,
    WiFi.status() == WL_CONNECTED,
    cloudStatus,
    warehousehealth,
    healthstatus
);
  delay(20000);   
}
void connectWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
void updateOLED(float temperature, float humidity, bool wifiStatus, bool cloudStatus, int warehousehealth, String healthstatus){
  display.clearDisplay();
  //  Title 
  display.setTextSize(1);
  display.setCursor(10, 0);
  display.println("SMART WAREHOUSE");
  display.drawLine(0, 10, 127, 10, WHITE);
  // Sensor Data 
  display.setCursor(0, 16);
  display.print("Temp : ");
  display.print(temperature, 1);
  display.print((char)247);   // Degree symbol
  display.print("C");
  display.setCursor(0, 28);
  display.print("Hum  : ");
  display.print(humidity, 1);
  display.print("%");
  display.drawLine(0, 40, 127, 40, WHITE);
  // WiFi Status 
  display.setCursor(0, 44);
  display.print("WiFi : ");
  if (wifiStatus)
    display.print("Connected");
  else
    display.print("Offline");
  // Cloud Status 
  display.setCursor(0, 54);
  display.print("Cloud: ");
  if (cloudStatus)
    display.print("Uploaded");
  else
    display.print("Failed");
  //  Warehouse Status
  display.setCursor(78, 54);
  if (temperature > TEMP_THRESHOLD || humidity > HUM_THRESHOLD)
    display.print("ALERT");
  else
    display.print("OK");
  display.display();
display.setCursor(0,44);
display.print("Health: ");
display.print(warehousehealth);
display.print("%");
display.setCursor(0,54);
display.print(healthstatus);
}
int calculatehealth(float temperature,float humidity){
    int tempScore = 0;
    int humScore = 0;
    // Temperature Score
    if (temperature >= 15 && temperature <= 25)
        tempScore = 50;
    else if (temperature > 25 && temperature <= 30)
        tempScore = 35;
    else
        tempScore = 15;
    // Humidity Score
    if (humidity >= 40 && humidity <= 60)
        humScore = 50;
    else if (humidity > 60 && humidity <= 70)
        humScore = 35;
    else
        humScore = 15;
    return tempScore + humScore;
}
void updateLEDs(int warehousehealth){
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(YELLOW_LED,LOW);
    digitalWrite(RED_LED,LOW);
    if (warehousehealth >= 90){
        // Good
        digitalWrite(GREEN_LED,HIGH);
    }
    else if (warehousehealth >= 60){
        // Fair
        digitalWrite(YELLOW_LED,HIGH);
    }
    else{
        // Poor 
        digitalWrite(RED_LED,HIGH);
    }
}
