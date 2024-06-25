#ifndef POTENTIOMETERS_HANDLER_H
#define POTENTIOMETERS_HANDLER_H

#include "constants.h"

int analogSliderValues[NUM_SLIDERS];
int previousSliderValues[NUM_SLIDERS];
const int ANALOG_THRESHOLD = 50;
void setUpSliders(){
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
    previousSliderValues[i] = -1;
  }
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    if(muted){
      analogSliderValues[i] = 0;
    }
    else{
      float raw =  analogRead(analogInputs[i]);
      analogSliderValues[i] = map(raw, 0, 4096, 0, 1024);
    }
  }
  masterVolume = (analogSliderValues[0] / 1023.0) * 100.0;
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);
    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

#endif