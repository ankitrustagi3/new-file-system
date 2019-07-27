#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sfs_utils.h"

#define MAX_FILE_NAME_LENGTH 12
#define MAX_FD 100
#define MAX_BYTES 30000
#define MIN_BYTES 10000

char * rand_name(){
  char fname[MAX_FILE_NAME_LENGTH];
  int i;

  for(i = 0; i < MAX_FILE_NAME_LENGTH; i++){
    if(i != 8){
      fname[i] = 'A' + (rand % 26);
    }
    else {
      fname[i] = '.'
    }
  }
  fname[i] = '\0';
  return (strdup(fname));
}

int main(){
  int i, j, k;
  int chunksize;
  char * buffer;
  int fds[MAX_FD];
  char * 
}
