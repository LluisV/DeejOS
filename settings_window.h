#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include "image_button.h"
#include "theme_handler.h"
#include "window.h"

class SettingsWindow : public Window {
public:
  // Access the singleton instance
  static SettingsWindow& getInstance() {
    static SettingsWindow instance; 
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
  SettingsWindow() {
    initButtons();
  }

  // Prevent copying and assignment
  SettingsWindow(const SettingsWindow&) = delete;
  SettingsWindow& operator=(const SettingsWindow&) = delete;

  const static int NUMBER_OF_BUTTONS = 2;
  const uint8_t *icons[NUMBER_OF_BUTTONS] = {theme_bmp, nullptr}; // Last one is null. It is reserevr for the back button
  void (*pressActions[NUMBER_OF_BUTTONS])() = {themeBtn_pressAction, nullptr};


  static void themeBtn_pressAction() {
    switchTheme();
  }

  static void backBtn_pressAction()
  {
    popWindow();
  }


  void initButtons() {
    int num_cols = 5;
    int num_rows = 2;

    float cell_width = WIDTH / num_cols;
    float cell_height = (HEIGHT - 50) / num_rows;

    int button_size =  48;

    for (int i = 0; i < NUMBER_OF_BUTTONS - 1; i++) {
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

    // BACK BUTTON
    buttons[NUMBER_OF_BUTTONS-1] = new ImageButton(&tft);
    static_cast<ImageButton*>(buttons[NUMBER_OF_BUTTONS-1])->initButtonUL(10, 15, 64, 64, FOREGROUND_COLOR, TFT_RED, BACKGROUND_COLOR, "", 1);
    static_cast<ImageButton*>(buttons[NUMBER_OF_BUTTONS-1])->setPressAction(SettingsWindow::backBtn_pressAction);

  }

  void drawButtons() {

    for(int i = 0; i < NUMBER_OF_BUTTONS-1; i++){
      static_cast<ImageButton*>(buttons[i])->drawImageButton();
    }
  }

  void drawHeader(){
    // Draw the back button
    tft.drawBitmap(10,15, back_bmp, 32, 32, FOREGROUND_COLOR);

    // Draw the title
    ofr.setDrawer(tft);
    ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
    ofr.setFontSize(70);
    ofr.setCursor(130, 5);
    ofr.cprintf("Settings");
  }

  void setDirty() override {
    initialized = false;
  }

};

#endif
