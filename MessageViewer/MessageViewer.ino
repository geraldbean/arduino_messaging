#include "MessageControls.h"

extern const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  MainMenu();
}

void loop() {
  // put your main code here, to run repeatedly:

}
