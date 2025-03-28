

#include <LiquidCrystal.h>
#include <Arduino.h>
#include <Wire.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

typedef enum {none,right,left,up,down,select} Button;

//LiquidCrystal *lcd;

//Data Structure
//-------------------------------------------------------------------//

typedef struct message {
    struct message *next;
    struct message *prev;
    char *message;
    int *IDs;
    int SenderID;
} Message, *pMessage;

typedef struct chat {
    pMessage latestMessage;
    int *IDsInvolved;
    struct chat *nextChat;
    struct chat *prevChat;
} Chat, *pChat;

typedef struct viewer {
    pChat firstChat;
} Viewer,*pViewer;

//------------------------------------------------------------------//

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //lcd = InitLCD(rs, en, d4, d5, d6, d7,16, 2);
  Startup();
  delay(1000);
  MainMenu();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}


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

void Startup(){
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
}

void MainMenu(){
  pViewer pMainMenu = CreateViewer();
  int ids[] = {10,20,30};
  int idsTwo[] = {40,50,60};
  int idsThree[] = {70,80,90};
  pMainMenu->firstChat = CreateChat(ids);
  AddChatToList(pMainMenu,idsTwo);
  AddChatToList(pMainMenu,idsThree);
  


  
  int menu = 0;
  Button button;
  while(1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Main Menu");
    lcd.setCursor(0,1);
    lcd.write("Send Message");

    button = CheckButton();
    
    if(button == right){
      if(menu == 0){
        menu = 1;
      }
      else{
        menu = 0;
      }
    }
    else if(button == left){
      if(menu == 0){
        menu = 1;
      }
      else{
        menu = 0;
      }
    }
    if(menu == 0){
      lcd.setCursor(0,1);
      lcd.write("Send Message");
      if(button == select){
        //Send Message Code Runs Here
      }
    }
    if(menu == 1){
      lcd.setCursor(0,1);
      lcd.write("Check Messages");
      if(button == select){
        ChatSelectMenu(pMainMenu,0);
      }
    }
    delay(250);
  }
}

void ChatSelectMenu(pViewer View,int chatIndex){
  pChat pCurrentChat = View->firstChat;
  Button button = CheckButton();

  delay(500);
  while(1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write("Chat with IDs:");
    button = CheckButton();
    if(button == up){
      return;
    }
    if(button == select){
      ViewChat(pCurrentChat);
    }
    else if(button == right){
      if(pCurrentChat->nextChat == NULL){
        while(button != left){
          button = CheckButton();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("No Chat Present");
          lcd.setCursor(0,1);
          lcd.print("Press Left");
          delay(250);
        }
        continue;
      }else{
        pCurrentChat = pCurrentChat->nextChat;
      }
      
    }
    else if(button == left){
      if(pCurrentChat->prevChat == NULL){
        while(button != right){
          button = CheckButton();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("No Chat Present");
          lcd.setCursor(0,1);
          lcd.print("Press Right");
          delay(250);
        }
        continue;
      }else{
        pCurrentChat = pCurrentChat->prevChat;
      }
    }
    lcd.setCursor(0,1);
    int *IDs = pCurrentChat->IDsInvolved;
    for(int i = 0; i < 3;i++){
      lcd.print(IDs[i]);
      lcd.setCursor((3*i)+3,1);
    }
    delay(250);
  }
}

int ViewChat(pChat chat){
  Button button = CheckButton();
  //Create the remainder of the view Chat Function
  //Will have to create some messages inside the chats created in the MainMenu Function for testing
  //have the list stop when you try to go to a message newer than newest one and tell you no messages available when you go past the last message
  while(1){
    button = CheckButton();
    if(button == up){
      return 1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("From:");
    lcd.setCursor(6,0);
    lcd.print("SenderID");
    lcd.setCursor(0,1);
    lcd.print("Message");
    delay(250);
  }
  
}




//Data Structures Functions
//------------------------------------------------------------------------//

pViewer CreateViewer(void){
    pViewer pnew = (pViewer)malloc(sizeof(Viewer));
    pnew->firstChat = NULL;
    return pnew;
}

pChat CreateChat(int IDs[]){
    pChat pnew = (pChat)malloc(sizeof(Chat));
    pnew->latestMessage = NULL;
    pnew->IDsInvolved = (int*) malloc(sizeof(IDs));
    pnew->IDsInvolved = IDs;
    pnew->nextChat = NULL;
    pnew->prevChat = NULL;
    return pnew;
}

pMessage CreateMessage(int IDs[], int SenderID, char *message){
    pMessage pnew = (pMessage) malloc(sizeof(Message));
    pnew->IDs = (int*) malloc(sizeof(IDs));
    pnew->IDs = IDs;
    pnew->SenderID = SenderID;
    pnew->message = (char*) malloc(sizeof(Message)*sizeof(char));
    pnew->message = message;
    
    pnew->next = NULL;
    pnew->prev = NULL;
    return pnew;
}


pChat FindChat(int IDs[],pViewer view){
    pChat pTempChat = view->firstChat;
    int numIDsInChat = sizeof(pTempChat->IDsInvolved)/sizeof(int);
    int numSameIDs = 0;

    int numIDsInSearch = sizeof(IDs)/sizeof(IDs[0]);

    //Edge case for if no chats exist at all
    if(pTempChat == NULL){
        pTempChat = CreateChat(IDs);
        return pTempChat;
    }

    //Finds first chat with name number of IDs involved
    while(1){
        //Finds the number of IDs in the current Chat
        numIDsInChat = sizeof(pTempChat->IDsInvolved)/sizeof(int);

        //Resets the number of Same IDs to 0 for the new check;
        numSameIDs = 0;

        //If the currently being searched chat's number of IDs does not match that in the search it skips to the next chat
        if(numIDsInChat != numIDsInSearch){
            //Checks if the next chat exists, if it doesnt, a new chat is created using the inputed message, senderID, and IDs then returns it
            if(pTempChat->nextChat == NULL){
                pTempChat->nextChat = CreateChat(IDs);
                return pTempChat->nextChat;
            }

            pTempChat = pTempChat->nextChat;
            //Refinds the number of IDs in the current chat now that the current chat has changed
            numIDsInChat = sizeof(pTempChat->IDsInvolved)/sizeof(int);
        }
        //Compares every ID in the array of the IDs we are trying to find to the IDs in the current chat
        //and adds one to the number of same IDs int for each matching one
        for(int i = 0; i < numIDsInChat; i++){
            for(int j = 0; j < numIDsInSearch; j++){
                if(pTempChat->IDsInvolved[i] == IDs[j]){
                    numSameIDs++;
                }
            }
        }
        
        

        //If the number of matching IDs is not equal to the number of IDs in the chat tempChat is moved to the next chat
        if(numIDsInChat != numSameIDs){
            //Checks if the next chat exists, if it doesnt, a new chat is created using the inputed message, senderID, and IDs then returns it
            if(pTempChat->nextChat == NULL){
                pTempChat->nextChat = CreateChat(IDs);
                return pTempChat->nextChat;
            }
            pTempChat = pTempChat->nextChat;
        }else{
            break;
        }
    }
    //Returns the chat with the same IDs involved
    return pTempChat;
}

int addMessageToChat(int IDs[],pChat chat, int SenderID, char *message){
    //No edge case for no messages in chat is needed because the chat will always have 1 message in it when its created for the first time;
    pMessage pnew = CreateMessage(IDs, SenderID, message);
    pMessage pRecent = chat->latestMessage;
    pnew->next = pRecent;
    pRecent->prev = pnew;
    chat->latestMessage = pnew;
    return 1;
}

int MessageRecieved(int IDs[],pViewer view, int SenderID, char *message){
    //Finds the correct chat for the IDs involved, the FindChat function will create a chat if one doesn't exist
    pChat chat = FindChat(IDs,view);

    //Adds a message to that chat
    int result = addMessageToChat(IDs,chat,SenderID,message);

    return 1;
}

int AddChatToList(pViewer view,int IDs[]){
  pChat pnew = CreateChat(IDs);
  pChat pStart = view->firstChat;
  pnew->nextChat = pStart;
  pStart->prevChat = pnew;
  view->firstChat = pnew;
  return 1;
}
