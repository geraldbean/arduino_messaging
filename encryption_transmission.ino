#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <math.h>
//Mar 4 6:51 PM

// LCD pin connections: RS, E, D4, D5, D6, D7
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SoftwareSerial hc12(10, 11);  
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Button pins
#define BTN_RIGHT  0    // ADC value for Right button
#define BTN_UP     99   // ADC value for Up button
#define BTN_DOWN   255  // ADC value for Down button
#define BTN_LEFT   410  // ADC value for Left button
#define BTN_SELECT 640  // ADC value for Select button
#define BTN_NONE   1023 // No button pressed
#define G 9
#define P 23

#define NUM_NODES 2    
#define INF 9999       
#define BUZZER_PIN 3 
#define MAX_TEXT 1

const int NODE_ID = 0;

// Variables
int destinationNode = 1;
char letters[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
//char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Available letters
int rowIndex = 0;  // Current letter
int tempLetterIndex=rowIndex;
int cursorPos = 0;    // Cursor column position on LCD
int tempCursorPos=cursorPos;
char selectedText[MAX_TEXT];
char typedText[17]; // Stores typed text
int textEmptyIndex=0;
bool flagPressed;//check if buttons were pressed or not
char boardAlphabet[2][13];
char boardPrint[16];
// int sent_package;

int graph[NUM_NODES][NUM_NODES] = {
    {0, 1},
    {1, 0}  
};

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
  textSetup(letters,boardAlphabet,boardPrint);
  pinMode(BUZZER_PIN, OUTPUT);


}

void loop() {
  receiveMessage();
  inputMessage();
  sendMessage();


  updateDisplay();
}

void receiveMessage() {
  if (hc12.available()) {
     
      int sender = (NODE_ID == 0) ? 1 : 0; // Infer sender based on NODE_ID
      int nextNode = (NODE_ID == 0) ? 1 : 0; 
      int destination = (NODE_ID == 0) ? 0 : 1; // Set destination dynamically

      String receivedData = hc12.readString();
      Serial.println("Received: " + receivedData);
      long unsigned int received_package = receivedData.toInt();
      long unsigned int decrypt = (long unsigned int)fmod(pow(received_package,3),P);


    if (NODE_ID == 1 && received_package == 4){
      Serial.println(received_package);
      // lcd.setCursor(0,0);
      // lcd.print(received_package);
      // float decrypt = (float)fmod(pow(5,received_package),P);
      // lcd.setCursor(1,1);
      // lcd.print(decrypt);
      playForwardTone();
    }
    //not sure about this bit.
      if (destination == NODE_ID) {
                lcd.clear();
                // lcd.print("Msg from ");
                // lcd.print(sender);
                lcd.setCursor(0, 1);
                lcd.print(decrypt);
                playReceiveTone();
                delay(3000);
                // lcd.print("Enter Msg:");
            }
            else if (nextNode != NODE_ID){
              return;
            }
  }
}

void sendMessage() {
  if (NODE_ID == 1 && selectedText[0] == 'A') {  // Only Node 1 sends
    while (hc12.available()) hc12.read(); // Clear HC-12 buffer

    long unsigned int sent_package = 4;
    long unsigned int encrypt = (long unsigned int)fmod(pow(G, sent_package), P);
    Serial.println(encrypt);
    hc12.println(encrypt);

    Serial.println("Message sent from Node 1 to Node 0");
    lcd.setCursor(0, 0);
    lcd.print("Sent to Node 0");

    selectedText[0] = '\0'; // Clear selectedText after sending
  }
}

void inputMessage(){
  int x=analogRead(0);
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
    if (cursorPos==15 && textEmptyIndex!=0){
      textEmptyIndex--;
      Serial.print("Deleted from msg:");
      Serial.println(selectedText[textEmptyIndex]);
      selectedText[textEmptyIndex]=NULL;
    }
    if (textEmptyIndex<MAX_TEXT){
      if (cursorPos<13){
        selectedText[textEmptyIndex] = boardPrint[cursorPos]; // Select letter
        Serial.print(selectedText[textEmptyIndex]);

        lcd.setCursor(0,0);
        lcd.print(selectedText[textEmptyIndex]);
        textEmptyIndex++;//increment to indicate next empty index
      }
    }else {
      Serial.print("Message Max Reached:");
      for(int i=0; i<MAX_TEXT;i++){
        //selectedText[] is the array for the string.
        Serial.print(selectedText[i]);
      }
      Serial.println("");
    }
    delay(200);
  }
}

void textSetup(char* letters, char boardAlphabet[2][13], char* boardPrint){
  lcd.begin(16, 2); // Set LCD size
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

// Function to use up/left/down/right buttons on LCD keypad shield to select 
// destination node
void selectDestination() {
    while (true) {
        receiveMessage();  // Always listen for incoming messages

        lcd.setCursor(0, 1);
        lcd.print("Node ");
        lcd.print(destinationNode);
        lcd.print("    ");

        int button = readButton();

        if (button == BTN_RIGHT || button == BTN_UP) {
            destinationNode = (destinationNode + 1) % NUM_NODES;  // Increment node, wrap around
            delay(200); // Debounce delay
        } else if (button == BTN_LEFT || button == BTN_DOWN) {
            destinationNode = (destinationNode - 1 + NUM_NODES) % NUM_NODES;  // Decrement node, wrap around
            delay(200); // Debounce delay
        } else if (button == BTN_SELECT) {
            lcd.clear();
            lcd.print("Dest Selected:");
            lcd.setCursor(0, 1);
            lcd.print("Node ");
            lcd.print(destinationNode);
            delay(1000);
            return;
        }
    }
}

int readButton() {
    int adc = analogRead(A0);
    delay(100);  // Debounce delay

    if (adc < 50) return BTN_RIGHT;  // Right button pressed
    if (adc < 150) return BTN_UP;     // Up button pressed
    if (adc < 300) return BTN_DOWN;   // Down button pressed
    if (adc < 500) return BTN_LEFT;   // Left button pressed
    if (adc < 800) return BTN_SELECT; // Select button pressed

    return BTN_NONE;  // No button pressed
}

void playSendTone() {
    tone(BUZZER_PIN, 1000, 200);
    delay(250);
    tone(BUZZER_PIN, 1200, 200);
}

void playForwardTone() {
    tone(BUZZER_PIN, 800, 100);  
    delay(150);
    tone(BUZZER_PIN, 1000, 100);
    delay(150);
}

void playReceiveTone() {
    int melody[] = { 262, 330, 392, 523 };
    for (int i = 0; i < 4; i++) {
        tone(BUZZER_PIN, melody[i], 200);
        delay(250);
    }
}
