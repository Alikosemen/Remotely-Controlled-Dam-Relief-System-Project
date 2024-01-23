#ifndef LcdController_h
#define LcdController_h

#include <LiquidCrystal_I2C.h>

class LcdController {
  public:
    LcdController(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows);
    void initialize();
    void printString(String str, uint8_t col, uint8_t row);
    void clear();
  private:
    LiquidCrystal_I2C _lcd;
};

#endif
