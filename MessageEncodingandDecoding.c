#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void messageEncoding(char *message,int *sendID, char *transmission){
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
    printf("2:%d\n",i);
    transmission[i] = mesgeLen;
    i++;
    int d = i;
    while(i < (mesgeLen + d)){
        transmission[i] = message[i-d];
        i++;
    }
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
    return 1;
    

    
}

int main(void){
    char msg[] = "HelloTesting102030405060708090";
    int ID[] = {10,20,30,76,99,12,24,62,13,0};
    char transmission[255];

    messageEncoding(msg,ID,transmission);
    /*printf("Number of people its being sent to: %d\n",transmission[0]);
    printf("Recipient ID: %d\n",transmission[1]);
    printf("Recipient ID: %d\n",transmission[2]);
    printf("Recipient ID: %d\n",transmission[3]);

    printf("Message Length: %d\n",transmission[4]);
    printf("Message is:\t");
    for(int i = 5; i < 10;i++){
        printf("%c",transmission[i]);
    }*/

    char *input = transmission;
    int currentID = 10;
    char outputMesg[255] = {'\0'};
    int outputIDs[255] = {0};

    int result = messageDecoding(input, currentID,outputMesg,outputIDs);
    if(result == 0){
        //Code for no message recieved
        printf("No message recieved");
    }
    if(result == 1){
        //sent outputMesg to print and the outputIDs to print
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