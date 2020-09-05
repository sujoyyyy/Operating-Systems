#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char* argv[]){
  int src; //source file
  int dst; //destination file
  int n; // tracking variable
  char buf[1];

  if(argc != 3){
    printf("Usage is of the following format: ./a.out sourceFileName destinationFileName\n");
    exit(1);
  }

  src = open(argv[1],O_RDONLY);
  if(src == -1){
    perror("can't find the source file");
    exit(1);
  }

  dst = creat(argv[2],777);
  dst = open(argv[2],O_WRONLY);
  if(dst == -1){
    perror("can't create or open destination file");
    exit(1);
  }

  while((n=read(src,buf,1))>0){
    write(dst,buf,1);
  }
  close(src);
  close(dst);
  return 0;
}