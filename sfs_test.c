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
      fname[i] = 'A' + (rand() % 26);
    }
    else {
      fname[i] = '.';
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
  char * names[MAX_FD];
  int filename[MAX_FD];
  int error_count = 0;
  int tmp;

  mksfs(1);

  for(i = 0; i < MAX_FILE_NAME_LENGTH; i++){
    names[i] = rand_name();
    fds[i] = sfs_open(names[i]);
    if(fds[i] < 0){
      fprintf(stderr, "The file does not exist!");
      error_count++;
    }
    tmp = open_files(names[i]);
    if(tmp >= 0 && tmp != fds[i]){
      fprintf(stderr, "The file does not exist!");
      error_count++;
    }
    filename[i] = (rand() % (MAX_BYTES - MIN_BYTES)) + MIN_BYTES;
  }

  printf("Opening the five files: \n");
  sfs_ls();
  for(i = 0; i < 5; i++){
    for(j = 0; j < filename[i]; j+=chunksize){
      if((filename[i] - j) < 10){
        chunksize = filename[i] - j;
      }
      else {
        chunksize = (rand() % (filesize[i] - j)) + 1;
      }
      if((buffer = malloc(chunksize)) == NULL){
        exit(-1);
      }
      for(k = 0; k < chunksize; k++){
        buffer[k] = (char)(j+k);
      }
      sfs_write(fds[i], buffer, chunksize);
      free(buffer);
    }
  }
}
