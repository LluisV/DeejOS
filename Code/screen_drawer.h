#ifndef SCREEN_DRAWER_H
#define SCREEN_DRAWER_H
#include "volume_window.h"
#include "home_window.h"
#include "constants.h"
#include "FreeSans20pt7b.h"
#include <stack>

std::stack<Window*> windowStack;

void setUpScreen()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BACKGROUND_COLOR);
  ofr.loadFont(TTF_FONT, sizeof(TTF_FONT));

  windowStack.push(&HomeWindow::getInstance());
}


void scanButtons()
{
  static uint32_t scanTime = millis();
  // Scan keys every 50ms at most
  if (millis() - scanTime >= 50) {
    scanTime = millis();
    windowStack.top()->scanButtons();
  }
}

// Push a new window onto the stack, updating the current window
void pushWindow(Window* newWindow)
{
  if (newWindow != nullptr) {
    tft.fillScreen(BACKGROUND_COLOR); // Clear the screen
    windowStack.push(newWindow);
  }
}

// Pop the current window from the stack, effectively returning to the previous one
void popWindow()
{
  tft.fillScreen(BACKGROUND_COLOR); // Clear the screen

  if (!windowStack.empty()) {
    windowStack.pop(); // Remove it from the stack
  }
  
  if (!windowStack.empty()) {
    windowStack.top()->setDirty(); // Ensure it will be drawn from scratch
    windowStack.top()->draw();
  }
}

void drawScreen()
{
  if (!windowStack.empty()) {
    windowStack.top()->draw();
  }
}

#endif