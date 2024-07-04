#ifndef VOLUME_WINDOW_H
#define VOLUME_WINDOW_H
#include "window.h"

// Define the VolumeWindow class that inherits from Window
class VolumeWindow : public Window {
public:

  static VolumeWindow& getInstance() {  
    static VolumeWindow instance;
    instance.setDirty();  
    return instance;
  }

  // Implement the draw method
  void draw() override {
    drawHeader();
    drawPotentiometers();
  }

  // If the window is set as dirty, it will be completely re-drawn from scratch
  void setDirty() override {
    // Here you should put the actions needed to be able to draw everything agin (reset to the inital state basically)
    initialized = false;
    initMeter = true;
  }

private:
  bool initMeter = true;
  uint16_t lastAngle[NUM_SLIDERS] = {30,30,30,30,30,30,30,30,30,30};
  ButtonWidget backBtn = ButtonWidget(&tft);

  VolumeWindow() {
    initButtons();
  }

  // Prevent copying and assignment
  VolumeWindow(const VolumeWindow&) = delete;
  VolumeWindow& operator=(const VolumeWindow&) = delete;

  static void backBtn_pressAction()
  {
    popWindow();
  }

  void initButtons() {
    backBtn.initButtonUL(10, 15, 64, 64, FOREGROUND_COLOR, TFT_RED, BACKGROUND_COLOR, "", 1);
    backBtn.setPressAction(VolumeWindow::backBtn_pressAction);
    //backBtn.drawSmoothButton(false, 3, BACKGROUND_COLOR); 
    buttons[0] = &backBtn;
  }


  void drawHeader(){
    // Draw the back button
    tft.drawBitmap(10,15, back_bmp, 32, 32, FOREGROUND_COLOR);

    // Draw the title
    ofr.setDrawer(tft);
    ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
    ofr.setFontSize(70);
    ofr.setCursor(130, 5);
    ofr.cprintf("Volume");
  }


  void drawPotentiometers(){
    int num_cols = 5;
    int num_rows = 2;
    float cell_width = WIDTH / num_cols;
    float cell_height = HEIGHT / num_rows;

    for (int row = 0; row < num_rows; row++) {
      for (int col = 0; col < num_cols; col++) {
        float x = cell_width / 2 + col * cell_width;
        float y = cell_height / 2 + row * cell_height;
        if(row == 0)
          y += 30;
        int pot = row * num_cols + col;
        float val = (analogSliderValues[pot] / 1023.0) * 100.0;
      
        if (abs(analogSliderValues[pot] - previousSliderValues[pot]) > HYSTERESIS || initMeter) {
          // Draw the potentiometer ring
          ringMeter(x, y, pot, 40, val, sliderNames[pot]);
          // Update the prev value
          previousSliderValues[pot] = analogSliderValues[pot];
        }
      }
    }
    initMeter = false;
  }

  
  void ringMeter(int x, int y, int i, int r, int val, const char *units)
  {
    uint16_t last_angle = lastAngle[i];

    if (initMeter) {
      last_angle = 30;
      tft.fillCircle(x, y, r, SURFACE_COLOR);
      tft.drawSmoothCircle(x, y, r, SURFACE_COLOR, SURFACE_COLOR);
      uint16_t tmp = r - 3;
      tft.drawArc(x, y, tmp + 1, tmp - tmp / 5 - 1, last_angle, 330, BACKGROUND_COLOR, SURFACE_COLOR);
    }

    r -= 3;

    // Range here is 0-100 so value is scaled to an angle 30-330
    int val_angle = map(val, 0, 100, 30, 330);
    
    if (last_angle != val_angle || initMeter) {

      ofr.setDrawer(spr); // Link renderer to sprite (font will be rendered in sprite spr)

      // Add value in centre if radius is a reasonable size
      if ( r >= 25 ) {
        // This code gets the font dimensions in pixels to determine the required the sprite size
        ofr.setFontSize((6 * r) / 4);
        ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);


        // The OpenFontRender library only has simple print functions...
        // Digit jiggle for changing values often happens with proportional fonts because
        // digit glyph width varies ( 1 narrower that 4 for example). This code prints up to
        // 3 digits with even spacing.
        // A few experimental fudge factors are used here to position the
        // digits in the sprite...
        // Create a sprite to draw the digits into
        uint8_t w = ofr.getTextWidth("444");
        uint8_t h = ofr.getTextHeight("4") + 4;
        spr.createSprite(w, h + 2);
        spr.fillSprite(SURFACE_COLOR); // (TFT_BLUE); // (DARKER_GREY);
        char str_buf[8];         // Buffed for string
        itoa (val, str_buf, 10); // Convert value to string (null terminated)
        uint8_t ptr = 0;         // Pointer to a digit character
        uint8_t dx = 4;          // x offset for cursor position
        if (val < 100) dx = ofr.getTextWidth("4") / 2; // Adjust cursor x for 2 digits
        if (val < 10) dx = ofr.getTextWidth("4");      // Adjust cursor x for 1 digit
        while ((uint8_t)str_buf[ptr] != 0) ptr++;      // Count the characters
        while (ptr) {
          ofr.setCursor(w - dx - w / 20, -h / 2.5);    // Offset cursor position in sprite
          ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
          ofr.rprintf(str_buf + ptr - 1);              // Draw a character
          str_buf[ptr - 1] = 0;                        // Replace character with a null
          dx += 1 + w / 3;                             // Adjust cursor for next character
          ptr--;                                       // Decrement character pointer
        }
        spr.pushSprite(x - w / 2, y - h / 2); // Push sprite containing the val number
        spr.deleteSprite();                   // Recover used memory

        // Make the TFT the print destination, print the units label direct to the TFT
        ofr.setDrawer(tft);
        ofr.setFontColor(FOREGROUND_COLOR, SURFACE_COLOR);
        ofr.setFontSize(r / 1.15);
        ofr.setCursor(x, y + (r * 1.4));
        ofr.cprintf(units);
      }
      
      // Allocate a value to the arc thickness dependant of radius
      uint8_t thickness = r / 5;
      if ( r < 25 ) thickness = r / 3;

      // Update the arc, only the zone between last_angle and new val_angle is updated
      if (val_angle > last_angle) {
        tft.drawArc(x, y, r, r - thickness, last_angle, val_angle, ACCENT_COLOR, BACKGROUND_COLOR); // TFT_SKYBLUE random(0x10000)
      }
      else {
        tft.drawArc(x, y, r + 1, r - thickness - 1, val_angle, last_angle, BACKGROUND_COLOR, SURFACE_COLOR);
      }
      lastAngle[i] = val_angle; // Store meter arc position for next redraw
    }
  }

};



#endif