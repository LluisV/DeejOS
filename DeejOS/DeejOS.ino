#include <FS.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <TFT_eWidget.h>
#include <BleKeyboard.h>
#include "bitmaps.h"
#include "NotoSans_Bold.h"
#include "OpenFontRender.h"
#include "constants.h"
#include "potentiometers_handler.h"
#include "touch_calibration.h"
#include "screen_drawer.h"
#include "switches_handler.h"
#include "dht11_handler.h"
#include "time_handler.h"

void setup() { 
  setupTheme();
  setUpScreen();
  touch_calibrate();
  setupDHT11();
  setupSwitches();
  setUpSliders();
  Serial.begin(500000);
  setupTime();
  bleKeyboard.begin();
}

void loop() {
  scanButtons();
  updateSliderValues();
  sendSliderValues();
  updateLocalTime();
  checkSwitchChange();
  updateTemperatureHumidity();
  drawScreen();
}







