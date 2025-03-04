#include <LiquidCrystal.h>
//Mar 4 5:55 PM -Eliana
//Summary: changed setup so letters can print

// LCD pin connections: RS, E, D4, D5, D6, D7
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Button pins
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5
#define SELECT 6

// Variables
char letters[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
int letterIndex = 0;  // Current letter
int cursorPos = 0;    // Cursor position on LCD
char typedText[17]; // Stores typed text

void setup() {
  // pinMode(LEFT, INPUT_PULLUP);
  // pinMode(RIGHT, INPUT_PULLUP);
  // pinMode(UP, INPUT_PULLUP);
  // pinMode(DOWN, INPUT_PULLUP);
  // pinMode(SELECT, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2); // Set LCD size
  lcd.setCursor(0,0);
  lcd.print("Select Letter:");
  lcd.setCursor(0,1);
  lcd.print(letters[0]);
  int letterIndex=0;
  for (int i=0;i<16;i++){
     lcd.setCursor(i,1);//set to second row's columns
     if (letters[letterIndex]){
      lcd.print(letters[letterIndex]);
     letterIndex+=2;
     }
     else lcd.print(" "); //ensures if no more letters doesn't print hieroglyphs
  }
  // // updateDisplay();
}

void loop() {
  if (digitalRead(LEFT) == LOW) {
    cursorPos = max(0, cursorPos - 1); // Move cursor left
    delay(200);
  }
  
  if (digitalRead(RIGHT) == LOW) {
    cursorPos = min(15, cursorPos + 1); // Move cursor right
    delay(200);
  }

  if (digitalRead(UP) == LOW) {
    letterIndex = (letterIndex + 1) % strlen(letters); // Next letter
    delay(200);
  }

  if (digitalRead(DOWN) == LOW) {
    letterIndex = (letterIndex - 1 + strlen(letters)) % strlen(letters); // Previous letter
    delay(200);
  }

  if (digitalRead(SELECT) == LOW) {
    typedText[cursorPos] = letters[letterIndex]; // Select letter
    delay(200);
  }

  updateDisplay();
}

void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print(typedText); // Show typed text

  lcd.setCursor(cursorPos, 1);
  lcd.blink(); // Blink at cursor position
}