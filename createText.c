#include <LiquidCrystal.h>
//Mar 27

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
#define MAX_TEXT 5

// Variables
char letters[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Available letters
int rowIndex = 0;  // Current letter
int tempLetterIndex=rowIndex;
int cursorPos = 0;    // Cursor column position on LCD
int msgPos=4;
char selectedText[MAX_TEXT];
char typedText[17]; // Stores typed text
int textEmptyIndex=0;
bool flagPressed;//check if buttons were pressed or not
char boardAlphabet[2][13];
char boardPrint[16];


void setup() {
  Serial.begin(9600);
  textSetup();
}

void loop() {
  inputMessage();

}

void inputMessage(){
  int x=analogRead(0);
  int tempCursorPos=cursorPos;

  if (x>800) flagPressed=0;
  //conditional of button press type and "&&" is to check if the flag was previously not being pressed
  //(thus ensuring any duration of button press will work)
 
  //if Right pressed
  if (x <6 && flagPressed==0) {
    flagPressed=1;
    tempCursorPos=cursorPos;
    cursorPos = min(15, tempCursorPos + 1); // Move cursor right
    lcd.setCursor(cursorPos,1);
    //Serial.print("new cursor position:"); //print statement checks
    //Serial.println(cursorPos);
  }
  //if Up pressed
  else if (x<200 && flagPressed==0) {
    if(cursorPos>12){
      //up button for our functions
    }else{
    flagPressed=1;
    // Serial.print("current cursors position:");
    // Serial.println(cursorPos);
    // Serial.print("current boardPrint[cursorPos] value");
    // Serial.println(boardPrint[cursorPos]);//print statement checks
    if(rowIndex==0){
      rowIndex=1;
    }else{
      rowIndex=0;
    }
    boardPrint[cursorPos] = boardAlphabet[rowIndex][cursorPos];
    lcd.print(boardPrint[cursorPos]);}
    delay(200);
  }
  //if Down pressed
  else if (x<400 && flagPressed==0) {
    flagPressed=1;  
    if(cursorPos>12){
      //up button for our functions
    }else{if(rowIndex==0){
      rowIndex=1;
    }else{
      rowIndex=0;
    }
    boardPrint[cursorPos] = boardAlphabet[rowIndex][cursorPos];
    lcd.print(boardPrint[cursorPos]);}
    delay(200);
  }
  //if Left pressed
  else if (x<600 && flagPressed==0) {
    flagPressed=1;
    tempCursorPos=cursorPos;
    cursorPos = max(0, tempCursorPos - 1); // Move cursor left
    lcd.setCursor(cursorPos,1);
    //Serial.print("new cursor position:");//check print statement
    //Serial.println(cursorPos);
  }
  //if Select pressed
  else if (x<800 && flagPressed==0) {
    //delete a letter
    if (cursorPos==15 && textEmptyIndex!=0){
      textEmptyIndex--;
      Serial.print("Deleted from msg:");
      Serial.println(selectedText[textEmptyIndex]);
      msgPos--;
      lcd.setCursor(msgPos,0);
      lcd.print(" ");
      selectedText[textEmptyIndex]=NULL;
    }
    //add letters
    if (textEmptyIndex<MAX_TEXT){
      if (cursorPos<13){
        selectedText[textEmptyIndex] = boardPrint[cursorPos]; // Select letter
        Serial.print(selectedText[textEmptyIndex]);
        lcd.setCursor(msgPos,0);
        lcd.print(selectedText[textEmptyIndex]);
        msgPos++;
        textEmptyIndex++;//increment to indicate next empty index
      }
    }else {
      Serial.print("Message Max Reached:");
      for(int i=0; i<MAX_TEXT;i++){
        Serial.print(selectedText[i]);
      }
      Serial.println("");
    }
    delay(200);
  }

  updateDisplay();
}

void textSetup(){
  lcd.begin(16, 2); // Set LCD size
  lcd.setCursor(0,0);
  lcd.print("Msg:");
  int letterIndexSetup=0;
  //setting up char array for board and its print array
  //Serial.println("boardAlphabet array:");//print statement check
  for (int i=0;i<13;i++){
    boardAlphabet[0][i]=letters[letterIndexSetup++];//puts it to letter index, then adds one to it for next letter
    boardAlphabet[1][i]=letters[letterIndexSetup++];
    boardPrint[i]=boardAlphabet[0][i];
    // Serial.print(boardAlphabet[0][i]);
    // Serial.print("  ");
    // Serial.println(boardAlphabet[1][i]);//print statement checks
  }
  for (int i=13;i<16;i++){
    boardPrint[i]= NULL;
  }
  //test print
  // //Serial.println("boardPrint array:");//print statement checks
  // for (int i=0;i<16;i++){
  //   Serial.print(boardPrint[i]);
  //   Serial.print("  ");
  // }
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

void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print(typedText); // Show typed text

  lcd.setCursor(cursorPos, 1);
  lcd.blink(); // Blink at cursor position
}