#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;
int main(int argc,char* argv[]) 
{
    int i, n, t1 = 0, t2 = 1, nextTerm;
    n=stoi(argv[0]);
    printf("\nFibonacci Series:\n");
    for (i = 1; i <= n; ++i) 
    {
        printf("%d\n", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

    _exit(0);
    return 0;

}