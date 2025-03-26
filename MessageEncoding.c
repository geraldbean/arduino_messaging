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

int main(void){
    char msg[] = "Hello";
    int ID[] = {10,20,30,0};
    char transmission[255];

    messageEncoding(msg,ID,transmission);
    printf("Number of people its being sent to: %d\n",transmission[0]);
    printf("Recipient ID: %d\n",transmission[1]);
    printf("Recipient ID: %d\n",transmission[2]);
    printf("Recipient ID: %d\n",transmission[3]);

    printf("Message Length: %d\n",transmission[4]);
    printf("Message is:\t");
    for(int i = 5; i < 10;i++){
        printf("%c",transmission[i]);
    }
    return 0;
}