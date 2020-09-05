/*F(n + 2) = F(n + 1) + F(n)
F(n + 3) = F(n + 1) + F(n + 2) = F(n + 1) * 2 + F(n)
F(n + 4) = F(n + 2) + F(n + 3) = F(n + 1) * 3 + F(n) * 2
F(n + 5) = F(n + 3) + F(n + 4) = F(n + 1) * 5 + F(n) * 3
F(n + 6) = F(n + 4) + F(n + 5) = F(n + 1) * 8 + F(n) * 5
Hopefully by now, we can see that:
F(n + k) = F(n + 1) * F(K) + F(n) * F(k - 1)*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;
int main(int argc,char* argv[]) 
{
    int i, n;
    n=stoi(argv[0]);
    int f[n+1];
    f[0]=0;
    f[1]=1;
    f[2]=1;
    printf("\nFibonacci Series:\n");
    printf("%d\n",f[0]);
    printf("%d\n",f[1]);
    printf("%d\n",f[2]);
    for (i = 2; i <= n; ++i) 
    {
        f[i+1]=f[2]*f[i]+f[1]*f[i-1];
        printf("%d\n",f[i+1]);
    }

    _exit(0);
    return 0;

}