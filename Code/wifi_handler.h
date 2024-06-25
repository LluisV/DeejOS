#include <WiFi.h>
#include "constants.h"


void connectWifi() {
  Serial.println("Connecting to WiFi.");
  WiFi.begin(ssid, password);

  int attemptCount = 0;
  const int maxAttempts = 5; // Maximum number of attempts before giving up

  ofr.setDrawer(tft);
  ofr.setFontColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
  ofr.setFontSize(40);
  ofr.setCursor(0, 120);
  ofr.printf("Connecting to wifi...");

  while (WiFi.status() != WL_CONNECTED && attemptCount < maxAttempts) {
    delay(250);
    Serial.print(".");
    attemptCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(WiFi.status());
    Serial.println("Failed to connect to WiFi. Please check your network configuration.");
    tft.fillScreen(BACKGROUND_COLOR);
    ofr.setCursor(0, 0);
    ofr.printf("Failed to connect to Wifi");
    delay(2000);
  }

  tft.fillScreen(BACKGROUND_COLOR);
}


void disconnectWifi(){
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  Serial.println("WiFi disconnected.");
}
