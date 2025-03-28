#ifndef MESSAGESTRUCTURE_H_
#define MESSAGESTRUCTURE_H_

#include <Arduino.h>

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

pViewer CreateViewer(void);

pChat CreateChat(int IDs[]);

pMessage CreateMessage(int IDs[], int SenderID, char *message);

pChat FindChat(int IDs[], pViewer view);

int addMessageToChat(int IDs[], pChat chat, int SenderID, char *message);

int MessageRecieved(int IDs[], pViewer view, int SenderID, char *message);

#endif