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
        printf("message passing failed\n");
        fprintf(stderr,"%s\n", strerror(errno));
        exit(-1);
    }
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("message passing failed\n");
        fprintf(stderr,"%s\n", strerror(errno));
        exit(-1);
    }
    printf("msgid: %d\n", msgid);
    printf("Write Data : "); 
    message.mesg_type = 10; 
    while(fgets(message.mesg_text, 100, stdin)){
        message.mesg_text[strlen(message.mesg_text)-1] = '\0';
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Data send is : %s \n", message.mesg_text);
        if(strcmp("exit", message.mesg_text) == 0)
            exit(0);
        printf("Write Data : ");
    }
} 

