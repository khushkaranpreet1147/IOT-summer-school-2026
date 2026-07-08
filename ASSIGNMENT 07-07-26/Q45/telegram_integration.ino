#include <HTTPClient.h>

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";

const char* BOT_TOKEN = "YOUR_BOT_TOKEN";
const char* CHAT_ID   = "YOUR_CHAT_ID";

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void sendTelegramAlert(String level) {

  if (WiFi.status() != WL_CONNECTED)
    return;

  HTTPClient http;

  String msg =
    "🚨 Motion Detected%0A"
    "Level: " + level +
    "%0ATime: " + String(millis()/1000) + " sec";

  String url =
    "https://api.telegram.org/bot" +
    String(BOT_TOKEN) +
    "/sendMessage?chat_id=" +
    String(CHAT_ID) +
    "&text=" +
    msg;

  http.begin(url);
  http.GET();
  http.end();
}

/*
In setup(), call:

connectWiFi();

------------------------------------

After:

alertSystem(alertLevel);

Add:

if(alertLevel==1)
  sendTelegramAlert("WARNING");
else if(alertLevel==2)
  sendTelegramAlert("ALARM");
else
  sendTelegramAlert("URGENT");

*/
