#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>


void history(char his[], char cmd[]) 
{
        strcat(his, "\n");
        strcat(his, cmd);
}
int main() {
        char cwd[128];
        char his[1000] = "";
        char rec[1];
        char cmd[100] = {
                0
        };
        int top = 0;
        int fd[2];             //inter process communication
        printf("\nSujoy's command shell\n\n");
        while (1) 
        {
                if (getcwd(cwd, sizeof(cwd)) == NULL) 
                {
                        perror("getcwd() error");
                        return 1;
                }

                pipe(fd);
                printf("\n");
                printf("\033[1;32m");
                printf("Different:");
                printf("\033[0m");
                printf("\033[1;34m");
                printf("~%s", cwd);
                printf("\033[0m");
                printf("@ ");
                fflush(stdout);
                scanf("%[^\n]%*c", cmd);

                if (strcmp(cmd, "history"))
                        printf("\n");
                history(his, cmd);
                if (strcmp(cmd, "exit") == 0) {
                        break;
                }
                char arg[10][100] = {
                        0
                };
                int argc = 0, count = 0;
                for (int i = 0; i < strlen(cmd); i++) {
                        if (cmd[i] == ' ') {
                                argc++;
                                count = 0;
                        } else {
                                arg[argc][count++] = cmd[i];
                        }
                }
                char * argv[10] = {
                        0
                };
                int k = 0;
                for (k = 0; k <= argc; k++) {
                        argv[k] = arg[k];
                }
                argv[k] = NULL;
                pid_t pid = fork();
                if (pid < 0) {
                        exit(1);
                } else if (pid == 0) {
                        if (!strcmp(cmd, "history")) {
                                printf("%s\n", his);
                        } else {
                                dup2(fd[1], 1);
                                if (execvp( * argv, argv) == -1)
                                        printf("Error executing \n");
                        }
                        exit(0);
                } else {
                        wait(NULL);
                        close(fd[1]);
                        while (read(fd[0], rec, 1) > 0) {
                                printf("%c", rec[0]);
                        }
                        close(fd[0]);
                }
        }
}