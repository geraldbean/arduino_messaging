#include <LiquidCrystal.h>
//Eliana was here
//RAH!!!!!!

// LCD pin connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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