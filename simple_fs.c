#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sfs_api.h"

#define MAX_FILE_NAME_LENGTH 12
#define MAX_FD 100
#define MAX 30000
#define MIN 10000

char *rand_name(){
  char fname[MAX_FILE_NAME_LENGTH];
  
  for(int counter = 0; counter < MAX_FILE_NAME_LENGTH; counter++){
    if(counter != 8) fname[counter] = 'A' + (rand() % 26)
    else fname[counter] = '.'
  }
  
  fname[counter] = '\0';
  return (strdup(fname));
}

int main(void){
   int i, j, k;
   
   int errorCount = 0;
   
   makefs(1);
   
   for(i = 0; i < 5; i++){
      names[i] = rand_name();
      fds[i] = sfs_open(names[i]);
      if(fds < 0){
          fprintf(stderr, "ERROR: creating first test file %s\n", names[i]);
          errorCount++;
      }
      tmp = sfs_open(names[i]);
      if(tmp >= 0 && fds[i] != tmp){
          fprintf(stderr, "ERROR: file %s has been opened twice\n", names[i]);
          errorCount++;
      }
      filesize[i] = (rand() % (MAX - MIN)) + MIN;
   }
  
   for(i = 0; i < 5; i++){
     for(j = i + 1; j < 2; j++){
        if(fds[i] == fds[j]){
           fprintf(stderr, "Warning: the file descriptors shouldn't be the same?\n");
        }
     }
   }
  
   printf("Five files created with zero length:\n");
   sfs_ls();
}


