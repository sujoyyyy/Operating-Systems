#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
int r1, c1, r2, c2;

void get_input(int a, int b, int array[][b]) {           //take input from the arrays
        for (int i = 0; i < a; i++)
                for (int j = 0; j < b; j++) {
                        scanf("%d", & array[i][j]);
                }
}

void display(int a, int b, int array[][b]) {            //display a 2-D array
        for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                        printf("%d ", array[i][j]);
                }

                printf("\n");
        }
}

int matmul(int a, int b, int a1[][c1], int a2[][c2])  //basic multiplication (RC)
{
        int sum = 0;
        for (int i = 0; i < r2; i++)
                sum += a1[a][i] * a2[i][b];
        return sum;
}

int main() {
        int status;

        printf("\nEnter the size of first:\n");
        scanf("%d %d", & r1, & c1);
        printf("Enter the size of second:\n");
        scanf("%d %d", & r2, & c2);

        int a[r1][c1];
        int b[r2][c2];

        printf("\nEnter the first =\n");
        get_input(r1, c1, a);
        printf("Enter the second =\n");
        get_input(r2, c2, b);

        printf("\nFirst Matrix :\n");
        display(r1, c1, a);
        printf("Second Matrix :\n");
        display(r2, c2, b);

        int c[r1][c2];
        printf("\nResult Computed:\n");
        pid_t pid[r1 * c2];
        int index = 0;
        int sum1, sum2;

        for (int i = 0; i < r1; i++) {

                for (int j = 0; j < c2; j += 2) {
                        pid[index] = vfork(); //use of vfork()
                        if (pid[index++] == 0) {
                                sum1 = matmul(i, j, a, b);
                                c[i][j] = sum1;
                                

                                _exit(0);
                        } else {
                                if (j + 1 < c2) {
                                        sum2 = matmul(i, j + 1, a, b);
                                        c[i][j + 1] = sum2;

                                      
                                }
                        }
                }
        }

        waitpid(-1, & status, 0);
        display(r1, c2, c);

        printf("\n");

        return 0;
}