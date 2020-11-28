#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100000
char command[MAX_COMMAND_LENGTH];

int main(int argc, char *argv[]){
    pid_t pid = 0;
    int ret = 0;
    printf("\nvincentinttsh:$");
    while(fgets (command, MAX_COMMAND_LENGTH, stdin)){
        command[strlen(command)-1] = '\0';
        pid = fork();
        if(strcmp("exit", command) == 0)
            exit(0);
        if(pid == 0){
            char** new_arg =  malloc((MAX_COMMAND_LENGTH / 2) * sizeof(char *));;
            unsigned long len = strlen(command), start = 0;
            char buffer[MAX_COMMAND_LENGTH];
            int now = 0;
            for(unsigned long i = 0; i < len; i++)
                if(command[i] == ' '){
                    char* buffer = malloc((i-start+10) * sizeof(char));
                    strncpy(buffer, command + start, i-start);
                    new_arg[now++] = buffer;
                    while(i+1 < len && command[i+1] == ' ')
                        i++;
                    start = i+1;
                }
            if (start != len){
                char* buffer = malloc((len-start+10) * sizeof(char));
                strncpy(buffer, command + start, len-start);
                new_arg[now++] = buffer;
            }
            new_arg[now] = NULL;
            ret = execvp(new_arg[0], new_arg);
            if (ret == -1){
                printf("\ncommand error");
                exit(-1);
            }
            for (int i = 0; i <= now; i++)
                free(new_arg[i]);
            free(new_arg);
        }else{
            wait(NULL);
        }
        printf("\nvincentinttsh:$");
    }
    exit(0);
}

