#include <LiquidCrystal.h>
//Eliana was here
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
int value = 100; 
int flag = 0; //when the button is pressed
int flagselect = 0;
int incre = 1; //the value I want to increment the left and right buttons by.
int incre2 = 10; //the value I want to increment the up and down buttons by.
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

// Button pins
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5
#define SELECT 6

// Variables
char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; // Available letters
int letterIndex = 0;  // Current letter
int cursorPos = 0;    // Cursor position on LCD
char typedText[17] = "                "; // Stores typed text

void setup() {
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  
  lcd.begin(16, 2); // Set LCD size
  lcd.print("Select Letter:");
  updateDisplay();
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