#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sfs_api.h"

#define MAX_FILE_NAME_LENGTH 12
#define MAX_FD 100

#define MAX_FILE_SIZE 30000
#define MIN_FILE_SIZE 10000

char *rand_name(){
  char fname[MAX_FILE_NAME_LENGTH];
  
  for(int counter = 0; counter < MAX_FILE_NAME_LENGTH; counter++){
    if(counter != 8) fname[counter] = 'A' + (rand() % 26)
    else fname[counter] = '.'
  }
  
  fname[counter] = '\0';
  return (strdup(fname));
}


