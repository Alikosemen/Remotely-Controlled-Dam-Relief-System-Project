#include "LcdController.h"

LcdController::LcdController(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows) : _lcd(lcdAddr, lcdCols, lcdRows) {}

void LcdController::initialize() {
  _lcd.init();
  _lcd.backlight();
}

void LcdController::printString(String str, uint8_t col, uint8_t row) {
  _lcd.setCursor(col, row);
  _lcd.print(str);
}

void LcdController::clear() {
  _lcd.clear();
}
