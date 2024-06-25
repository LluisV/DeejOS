#include <EEPROM.h>
#include "constants.h"

uint16_t darkModeAddress = 0;

void setupTheme(){
  // Initialize EEPROM with default value if it hasn't been initialized before
  EEPROM.begin(2);
  if (EEPROM.read(darkModeAddress) != 0 && EEPROM.read(darkModeAddress) != 1) {
    // Default value (false for light mode)
    EEPROM.write(darkModeAddress, 0);
    EEPROM.commit();
  }
  EEPROM.end();

  // Read dark mode setting from EEPROM
  EEPROM.begin(2);
  dark_mode = EEPROM.read(darkModeAddress);
  EEPROM.end();

  // Apply theme based on dark mode setting
  if (dark_mode) {
    BACKGROUND_COLOR = BACKGROUND_DARK_COLOR;
    SURFACE_COLOR = SURFACE_DARK_COLOR;
    FOREGROUND_COLOR = FOREGROUND_DARK_COLOR;
    ACCENT_COLOR = ACCENT_DARK_COLOR;
  } else {
    BACKGROUND_COLOR = BACKGROUND_LIGHT_COLOR;
    SURFACE_COLOR = SURFACE_LIGHT_COLOR;
    FOREGROUND_COLOR = FOREGROUND_LIGHT_COLOR;
    ACCENT_COLOR = ACCENT_LIGHT_COLOR;
  }
}


void saveDarkModeSetting(bool darkMode) {
  // Save the value of darkMode to EEPROM
  EEPROM.begin(2);
  EEPROM.write(darkModeAddress, darkMode);
  EEPROM.commit();
  EEPROM.end();
}

void switchTheme(){
  dark_mode = !dark_mode;
  if (dark_mode) {
    BACKGROUND_COLOR = BACKGROUND_DARK_COLOR;
    SURFACE_COLOR = SURFACE_DARK_COLOR;
    FOREGROUND_COLOR = FOREGROUND_DARK_COLOR;
    ACCENT_COLOR = ACCENT_DARK_COLOR;
  } else {
    BACKGROUND_COLOR = BACKGROUND_LIGHT_COLOR;
    SURFACE_COLOR = SURFACE_LIGHT_COLOR;
    FOREGROUND_COLOR = FOREGROUND_LIGHT_COLOR;
    ACCENT_COLOR = ACCENT_LIGHT_COLOR;
  }
  saveDarkModeSetting(dark_mode);
  ESP.restart();
}
