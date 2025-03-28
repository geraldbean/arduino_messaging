#include "MessageControls.h"




Button CheckButton(){
  Button button; 
  int input = analogRead(A0);
  if (input < 60) button = right;
  else if ((input > 60) && (input < 200)) {
    button = up;
  }
  else if ((input > 200) && (input < 400)) {
    button = down;
  }
  else if ((input > 400) && (input < 600)) {
    button = left;
  }
  else if ((input < 800) && (input >= 600)) {
    button = select;
  }
  else {
    button = none;
  }
  return button;
}

void MainMenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Main Menu");
  lcd.setCursor(0,1);
  lcd.write("Send Message");
}

void ChatSelectMenu(pViewer View,int chatIndex);

int ViewChat(pChat chat);