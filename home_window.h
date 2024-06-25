#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include "image_button.h"
#include "settings_window.h"
#include "window.h"

// Singleton class HomeWindow inheriting from Window
class HomeWindow : public Window {
public:
  // Access the singleton instance
  static HomeWindow& getInstance() {
    static HomeWindow instance; // Guaranteed to be lazily initialized, thread-safe in C++11 and later
    return instance;
  }

  // Implement the draw method
  void draw() override {
    drawHeader();
    if (initialized)
      return;
    initialized = true;
    drawButtons(); // Draw the buttons
  }

private:
  // Constructor must be private for singleton pattern
  HomeWindow() {
    initButtons();
  }

  // Prevent copying and assignment
  HomeWindow(const HomeWindow&) = delete;
  HomeWindow& operator=(const HomeWindow&) = delete;

  const static int NUMBER_OF_BUTTONS = 7;
  const uint8_t *icons[NUMBER_OF_BUTTONS] = {audio_bmp, coding_bmp, lights_bmp, games_bmp, weather_bmp, playpause_bmp, settings_bmp};
  void (*pressActions[NUMBER_OF_BUTTONS])() = {audioBtn_pressAction, codingBtn_pressAction, nullptr, nullptr, nullptr, playpauseBtn_pressAction, settingsBtn_pressAction};

  static void audioBtn_pressAction() {
    // Sample action for audio button press
    pushWindow(&VolumeWindow::getInstance());
  }

  static void codingBtn_pressAction() {
    if (getInstance().buttons[2]->justPressed())
      bleKeyboard.write(KEY_F13);
  }

  static void playpauseBtn_pressAction() {
    if (getInstance().buttons[5]->justPressed())
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  }

  static void settingsBtn_pressAction() {
    if (getInstance().buttons[6]->justPressed())
      pushWindow(&SettingsWindow::getInstance());
  }

  void initButtons() {
    int num_cols = 5;
    int num_rows = 2;

    float cell_width = WIDTH / num_cols;
    float cell_height = (HEIGHT - 50) / num_rows;

    int button_size =  48;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
      int row = i / num_cols;
      int col = i % num_cols;

      float x = cell_width / 2 + col * cell_width;
      float y = cell_height / 2 + row * cell_height + 45;
      if (row == 0)
          y += 30;

      buttons[i] = new ImageButton(&tft);
      static_cast<ImageButton*>(buttons[i])->initImageButton(x - button_size/2 - 10, y - button_size/2, 25, icons[i], button_size, button_size, FOREGROUND_COLOR);
      static_cast<ImageButton*>(buttons[i])->setPressAction(pressActions[i]);
    }
  }

  void drawButtons() {

    for(int i = 0; i < NUMBER_OF_BUTTONS; i++){
      static_cast<ImageButton*>(buttons[i])->drawImageButton();
    }
  }

  void setDirty() override {
    initialized = false;
  }

  int prevMasterVolume = -1;
  float prevTemperature = -1;
  float prevHumidity = -1;
  int prevMinutes = -1;
  int prevDay = -1; // Initialize to an invalid value

  void drawHeader(){
    // Set the initial positions and distances
    int text_icon_distance = 35;
    int items_distance = 25;
    int iconSize = 22; // Assuming the icon size is 22x22 pixels
    int yPos = 15;

    // We only draw the icons once
    if(!initialized)
    {
      // Draw the volume icon
      tft.drawBitmap(270, yPos, volume_bmp, iconSize, iconSize, FOREGROUND_COLOR);
      // Draw the temperature icon
      tft.drawBitmap(330, yPos, temperature_bmp, iconSize, iconSize, FOREGROUND_COLOR);
      // Draw the humidity icon
      tft.drawBitmap(400, yPos, humidity_bmp, iconSize, iconSize, FOREGROUND_COLOR);
    }

    // Update time if changed
    if(getLocalTime(&timeinfo))
    {
      char formattedTime[32]; // Buffer to store the formatted time string
      strftime(formattedTime, sizeof(formattedTime), "%H:%M", &timeinfo);
      int currentMinutes = timeinfo.tm_min;
      // Check if the minutes have changed
      if (currentMinutes != prevMinutes || !initialized) {
        prevMinutes = currentMinutes; // Update the previous minutes
        // Clear the previous time on the display
        tft.fillRect(20, yPos, 50, 25, BACKGROUND_COLOR);
        
        // Display the current time
        ofr.setDrawer(tft);
        ofr.setFontColor(FOREGROUND_COLOR, BACKGROUND_COLOR);
        ofr.setFontSize(28);
        ofr.setCursor(20, yPos);
        String timeStr = String(formattedTime);
        ofr.printf(timeStr.c_str());
      }
      
      int currentDay = timeinfo.tm_mday;

      if(currentDay != prevDay || !initialized){
        // Format the current date
        char formattedDate[64];
        strftime(formattedDate, sizeof(formattedDate), "%A, %B %d", &timeinfo);
        
        // Clear the previous date on the display (adjust coordinates as needed)
        tft.fillRect(0, yPos + 45, WIDTH, 30, BACKGROUND_COLOR);
        
        // Display the current date
        ofr.setFontSize(48);
        ofr.setCursor(WIDTH / 2, yPos + 40);
        ofr.cprintf(formattedDate);
        
        // Update the previous day
        prevDay = currentDay;
      }
    }

    // Update volume if changed
    if (abs(prevMasterVolume - masterVolume) > 2 || !initialized) { // To avoid noise
      // Clear the volume text area
      tft.fillRect(300, yPos, 28, 25, BACKGROUND_COLOR);
      // Draw the volume text
      ofr.setDrawer(tft);
      ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
      ofr.setFontSize(28);
      ofr.setCursor(300, yPos);
      String volumeStr = String(masterVolume);
      ofr.printf(volumeStr.c_str());
      // Update prevMasterVolume
      prevMasterVolume = masterVolume;
    }
    
    // Update temperature if changed
    if (prevTemperature != temperature ||!initialized) {

      // Clear the temperature text area
      tft.fillRect(355, yPos, 45, 25, BACKGROUND_COLOR);

      // Draw the temperature text
      ofr.setDrawer(tft);
      ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
      ofr.setFontSize(28);
      ofr.setCursor(355, yPos);
      String tmpStr = String(temperature);
      ofr.printf(tmpStr.c_str());

      // Update prevTemperature
      prevTemperature = temperature;
    }

    // Update humidity if changed
    if (prevHumidity != humidity ||!initialized) {
      // Clear the humidity text area
      tft.fillRect(425, yPos, 45, 25, BACKGROUND_COLOR);

      // Draw the humidity text
      ofr.setDrawer(tft);
      ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
      ofr.setFontSize(28);
      ofr.setCursor(425, yPos); 
      String humStr = String(humidity);
      ofr.printf(humStr.c_str());

      // Update prevHumidity
      prevHumidity = humidity;
    }
  }

};

#endif
