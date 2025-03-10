#include <LiquidCrystal.h>
//Mar 4 6:51 PM

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
//char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Available letters
int letterIndex = 0;  // Current letter
int cursorPos = 0;    // Cursor column position on LCD
char typedText[17]; // Stores typed text
bool flagPressed;//check if buttons were pressed or not
char boardAlphabet[2][16];
char boardPrint[16];


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Set LCD size
  lcd.setCursor(0,0);
  lcd.print("Select Letter:");
  lcd.setCursor(0,1);
  lcd.print(letters[0]);
  int letterIndexSetup=0;
  //setting up char array for board and its print array
  for (int i=0;i<16;i++){
    boardAlphabet[0][i]=letters[letterIndexSetup++];//puts it to letter index, then adds one to it for next letter
    boardAlphabet[1][i]=letters[letterIndexSetup++];
    boardPrint[i]=boardAlphabet[0][i];
  }
  letterIndexSetup=0;
  for (int i=0;i<16;i++){
    lcd.setCursor(i,1);//set to second row's columns
    if (boardPrint[i]){
     lcd.print(boardPrint[i]);
    }
    else lcd.print(" "); //ensures if no more letters doesn't print hieroglyphs
 }
  lcd.setCursor(0,1);
  // // updateDisplay();
}

void loop() {
  int x=analogRead(0);
  if (x>800) flagPressed=0;
  //conditional of button press type and "&&" is to check if the flag was previously not being pressed 
  //(thus ensuring any duration of button press will work)
  
  //if Right pressed
  if (x <6 && flagPressed==0) {
    flagPressed=1;
    cursorPos = min(15, cursorPos + 1); // Move cursor right
    lcd.setCursor(cursorPos,1);
  }
  //if Up pressed
  else if (x<200 && flagPressed==0) {
    flagPressed=1;
    letterIndex = (letterIndex + 1) % strlen(letters); // Next letter
    delay(200);
  }
  //if Down pressed
  else if (x<400 && flagPressed==0) {
    flagPressed=1;
    letterIndex = (letterIndex - 1 + strlen(letters)) % strlen(letters); // Previous letter
    delay(200);
  }
  
  else if (x<600 && flagPressed==0) {
    flagPressed=1;
    cursorPos = max(0, cursorPos - 1); // Move cursor left
    lcd.setCursor(cursorPos,1);
  }
  //if Select pressed
  else if (x<800 && flagPressed==0) {
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