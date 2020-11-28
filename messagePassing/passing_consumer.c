#include <stdio.h> 
#include <stdlib.h>  
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <errno.h>
#include <string.h>

extern int errno;

struct mesg_buffer { 
    long mesg_type; 
    char mesg_text[100]; 
} message;

int main() { 
    key_t key = ftok("/etc/hosts", 65);
    if (key == -1) {
        printf("get key failed\n");
        fprintf(stderr,"%s\n", strerror(errno));
        exit(-1);
    }
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("get msgid failed\n");
        fprintf(stderr,"%s\n", strerror(errno));
        exit(-1);
    }
    printf("msgid: %d\n", msgid);
    while (1) {
        msgrcv(msgid, &message, sizeof(message), 0, 0);
        if(errno != 0){
            printf("get message passing failed\n");
            fprintf(stderr,"%s", strerror(errno));
            exit(-1);
        }
        printf("Data Received is : %s \n",  message.mesg_text);
        if(strcmp("exit", message.mesg_text) == 0){
            msgctl(msgid, IPC_RMID, NULL);
            if(errno != 0){
                printf("fail to delete message queue\n");
                fprintf(stderr,"%s", strerror(errno));
                exit(-1);
            }
            printf("end message passing\n");
            exit(0);
        }
    }
} 

