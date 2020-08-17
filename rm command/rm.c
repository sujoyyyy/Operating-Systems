#include <stdio.h>

int main(int argc, char *argv[])
{
  int status;
  if(argc!=2){
    printf("Wrong usage-----------Correct usage: ./myrm file_name\n");
    return 0;
  }
  

  status = remove(argv[1]);

  if (status == 0)
    printf("%s file deleted successfully.\n", argv[1]);
  else
  {
    printf("Unable to delete the file\n");
    perror("Following error occurred");
  }

  return 0;
}