#include "MessageStructure.h"

pViewer CreateViewer(void){
    pViewer pnew = (pViewer)malloc(sizeof(Viewer));
    pnew->firstChat = NULL;
    return pnew;
}

pChat CreateChat(int IDs[]){
    pChat pnew = (pChat)malloc(sizeof(Chat));
    pnew->latestMessage = NULL;
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