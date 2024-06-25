#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H


#include "constants.h"    // Include your required constants or other headers


class ImageButton : public ButtonWidget {
public:
    // Constructor that takes a TFT_eSPI pointer
    ImageButton(TFT_eSPI *tft)
        : ButtonWidget(tft), _bitmap(nullptr), _w(0), _h(0), _fgcolor(FOREGROUND_COLOR) {}

    // Initialize the ImageButton with bitmap and position parameters
    void initImageButton(int x, int y, int padding, const uint8_t *bitmap, int w, int h, uint16_t fgcolor) {
        initButtonUL(x, y, w + padding, h + padding, FOREGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, "", 1); // Basic initialization
        _x = x;
        _y = y;
        _bitmap = bitmap;
        _w = w;
        _h = h;
        _padding = padding;
        _fgcolor = fgcolor;
    }

    // Method to draw the button with an optional bitmap
    void drawImageButton(bool smooth = true, int outlineWidth = 3, uint16_t bgcolor = BACKGROUND_COLOR) {
        if (smooth) {
            drawSmoothButton(false, outlineWidth, bgcolor); // Draw with smooth edges
        } else {
            drawButton(false); // Draw a regular button
        }

        if (_bitmap) {
            tft.drawBitmap(_x + _padding/2, _y+ _padding/2, _bitmap, _w, _h, _fgcolor); // Draw the bitmap if it exists
        }
    }

private:
  int _padding;
    int _x, _y;                  // Coordinates for the button's upper-left corner
    const uint8_t *_bitmap;      // Bitmap data pointer
    int _w, _h;                  // Bitmap width and height
    uint16_t _fgcolor;           // Bitmap foreground color
};

#endif // IMAGE_BUTTON_H
