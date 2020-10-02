#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>


FILE * openFile(char * filename) // open a file in read mode and return the pointer
{
        FILE * file;
        file = fopen(filename, "r");

        if (!file) {
                printf("Error!\n");
                return NULL;
        }

        return file;
}

void outputResults(int * charCount) {
        long numLetters = 0;
        long totalChars = 0;

        for (int i = 32; i < 128; i++) {
                totalChars += charCount[i];
                if (i >= 97 && i <= 122)
                        numLetters += charCount[i];
        }

        printf("\n\t Alphabets\n\n");
       printf("| Letter |  Count\t  [%%]\n");
       

        for (int i = 97; i < 123; i++) {
                printf("|   %c    |  %0d ", i, charCount[i]);
                printf("  \t%.2f%%\t\t", ((double) charCount[i] / numLetters) * 100);
                printf("\n");
        }

        printf("\n\t STATISTICS \n\n");
        printf("| Char Type |  Count\t  [%%]\n");
        printf("|---------- | ---------------------\n");

        printf("|  Letters  |  %li", numLetters);
        printf(" \t[%.2f%%]  |\n", ((double) numLetters / totalChars) * 100);
        printf("|  Other    |  %li", totalChars - numLetters);
        printf(" \t[%.2f%%]  |\n", ((double)(totalChars - numLetters) / totalChars) * 100);
        printf("|  Total    |  %li\t\t  |\n\n", totalChars);
}

int * countLetters(char * filename) {
        int * charCount;
        FILE * file;

        charCount = mmap(NULL, 128 * sizeof( * charCount), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

        for (int i = 0; i < 27; i++) {
                int c;

                if ((file = openFile(filename)) == NULL) {
                        printf("Error opening file. %d!\n", getpid());
                        exit(1);
                }

                pid_t pid = fork();

                if (pid == -1) {
                        exit(1);
                } else if (pid == 0) {
                        while ((c = tolower(fgetc(file))) != EOF) {
                                if (i == 26 && (c < 97 || c > 122))
                                        charCount[c]++; // Count other char
                                else if (c == i + 97)
                                        charCount[i + 97] += 1; // Count letters
                        }

                        fclose(file);
                        exit(0);
                } else
                        rewind(file);
        }

        for (int i = 0; i < 27; i++)
                wait(NULL);

        return charCount;
}

int main(int argc, char * argv[]) //command line arguments
{
        if (argc != 2) 
        {
                printf("Syntax: ./a.out <filename>\n");
                return 1;
        }

        char * filename = argv[1];
        FILE * file;

        if ((file = openFile(filename)) == NULL)
                return 1;

        outputResults(countLetters(filename));

        if (fclose(file) != 0) {
                printf("Error closing file!\n");
                return 1;
        }

        return 0;
}