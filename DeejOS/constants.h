#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TTF_FONT NotoSans_Bold
// This is the file name used to store the calibration data
// You can change this to create new calibration files.
// The SPIFFS file name must start with "/".
#define CALIBRATION_FILE "/TouchCalData2"
// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.c:\Users\lluis\Desktop\Repositoris\ESP32\Stream deck\custom_stream_deck\constants.h
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false
const int WIDTH = 480;
const int HEIGHT = 320;
const int HYSTERESIS = 10;
const int NUM_SLIDERS = 10;

const char* sliderNames[NUM_SLIDERS] = {"Master", "Current", "Unmapped", "System", "Mic", "Chrome", "Discord", "Spotify", "?", "?"};
const int analogInputs[NUM_SLIDERS] = {26, 27, 14, 12, 13, 25, 33, 32, 35, 34};
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft); 
OpenFontRender ofr;
BleKeyboard bleKeyboard;

int masterVolume = -1;
float temperature = -1;
float humidity = -1;
bool muted = false;

// WIFI
const char* ssid     = "*******"; // REPLACE WITH YOUR WIFI SSID
const char* password = "*******"; // REPLACE WITH YOUR WIFI PASSWORD

// TIME
const char* ntpServer = "pool.ntp.org";
struct tm timeinfo;

// THEME
bool dark_mode = false;
const uint16_t BACKGROUND_LIGHT_COLOR = 0xFFFF; 
const uint16_t SURFACE_LIGHT_COLOR = 0xef7d; 
const uint16_t FOREGROUND_LIGHT_COLOR = 0x0000; 
const uint16_t ACCENT_LIGHT_COLOR = 0x029b; 

const uint16_t BACKGROUND_DARK_COLOR = 0x0000; 
const uint16_t SURFACE_DARK_COLOR = 0x18E3; 
const uint16_t FOREGROUND_DARK_COLOR = 0xFFFF; 
const uint16_t ACCENT_DARK_COLOR = 0x667f; 

uint16_t BACKGROUND_COLOR = 0xFFFF; 
uint16_t SURFACE_COLOR = 0xef7d; 
uint16_t FOREGROUND_COLOR = 0x0000; 
uint16_t ACCENT_COLOR = 0x44bf; 


#endif