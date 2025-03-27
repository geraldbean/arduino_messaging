#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void messageEncoding(int ownID ,char *message,int *sendID, char *transmission){
    int mesgeLen = 0;
    while(1){
        if(message[mesgeLen] == '\0'){
            break;
        }
        mesgeLen++;
    }

    int numSend = 0;
    while(1){
        if(sendID[numSend] == 0){
            break;
        }
        numSend++;
    }
    
    int i = 0;
    transmission[i] = numSend;
    for(i = 1; i <= numSend; i++){
        transmission[i] = sendID[i-1];
    }
    transmission[i] = mesgeLen;
    i++;
    int d = i;
    while(i < (mesgeLen + d)){
        transmission[i] = message[i-d];
        i++;
    }
    transmission[i] = ownID;
    return;
    
}

int messageDecoding(char *input,int currentID, char *message, int IDsInMessage[]){
    int IDnum = input[0];
    int IDs[IDnum];
    for(int i = 1; i < IDnum + 1;i++){
        IDs[i-1] = input[i];
    }
    int isIn = 0;
    for(int i = 0; i < IDnum; i++){
        if(IDs[i] == currentID){
            isIn = 1;
        }
    }
    if(isIn == 0){
        return 0;
    }

    int MesgNum = input[IDnum + 1];

    for(int i = 1; i < MesgNum + 1; i++){
        message[i-1] = input[i + IDnum + 1];
    }
    int i = 0;
    int j = 0;
    while(i < IDnum){
        if(IDs[i] != currentID){
            IDsInMessage[j] = IDs[i];
            j++; 
        }
        i++;
    }
    i = 0;
    while(input[i] != '\0'){
        i++;
    }
    i--;
    return input[i];
    

    
}

int main(void){
    char msg[] = "Testing";
    int OwnID = 5;
    int ID[] = {10,20,30,0};
    char transmission[255] = {'\0'};

    messageEncoding(OwnID,msg,ID,transmission);
    /*printf("Number of people its being sent to: %d\n",transmission[0]);
    printf("Recipient ID: %d\n",transmission[1]);
    printf("Recipient ID: %d\n",transmission[2]);
    printf("Recipient ID: %d\n",transmission[3]);

    printf("Message Length: %d\n",transmission[4]);
    printf("Message is:\t");
    for(int i = 5; i < 10;i++){
        printf("%c",transmission[i]);
    }*/

    int currentID = 10;
    char outputMesg[255] = {'\0'};
    int outputIDs[255] = {0};

    int result = messageDecoding(transmission, currentID,outputMesg,outputIDs);
    if(result == 0){
        //Code for no message recieved
        printf("No message recieved");
    }
    if(result != 0){
        //sent outputMesg to print and the outputIDs to print
        printf("ID of sender is: %d\n",result);
        printf("Message is:");
        for(int i = 0; outputMesg[i] != '\0';i++){
            printf("%c",outputMesg[i]);
        }
        printf("\n");
        printf("IDs in message:");
        for(int i = 0; outputIDs[i] != 0;i++){
            printf("%d, ",outputIDs[i]);
        }
    }
    return 0;
}