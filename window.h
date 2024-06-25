#ifndef WINDOW_H
#define WINDOW_H
#define MAX_BTN 11

class Window {
public:

  Window(){
  }

  virtual ~Window() {
  }

  virtual void draw() = 0;
  virtual void setDirty() = 0;
  virtual void initButtons() = 0;

  void scanButtons()
  {
    uint16_t t_x = 9999, t_y = 9999; // To store the touch coordinates
    // Pressed will be set true if there is a valid touch on the screen
    bool pressed = tft.getTouch(&t_x, &t_y);
    for (uint8_t b = 0; b < MAX_BTN; b++) {
        // Check if the current button is not null before performing actions
        if (buttons[b] != nullptr) {
            if (pressed) {
                // If a touch is detected and the touch is within the button's bounds
                if (buttons[b]->contains(t_x, t_y)) {
                    buttons[b]->press(true); // Indicate button is pressed
                    buttons[b]->pressAction(); // Perform button press action
                }
            } else {
                buttons[b]->press(false); // Indicate button is not pressed
                buttons[b]->releaseAction(); // Perform button release action
            }
        }
    }
  }

protected:
  ButtonWidget* buttons[MAX_BTN] = {nullptr};
  bool initialized = false;
};

// Forward declaration to avoid cyclic dependencies
void pushWindow(Window* newWindow);
void popWindow();

#endif