#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "disk_emu.h"

FILE *fp = null;
double L, p;
double r;
int BLOCK_SIZE, MAX_BLOCK, MAX_RETRY, lru;

int close_disk(){
  if(fp != NULL){
    fclose(fp);
  }
  return 0;
}

int init_fresh_disk(char * filename, int block_size, int num_blocks){
    int i, j;

    L = 00000.f;
    p = -1.f;
    MAX_RETRY = 3;

    BLOCK_SIZE = block_size;
    MAX_BLOCK = num_blocks;

    srand((unsigned int)(time(0)));

    fp = fopen(filename, "w+b");

    if(fp == NULL){
      printf("Could not create the disk file.");
      return -1;
    }

    for(int i = 0; i < MAX_BLOCK; i++){
      for(j = 0; j < BLOCK_SIZE; j++){
        fputc(0, fp);
      }
    }
}

int init_disk(char * filename, int block_size, int num_blocks){
  int i, j;

  L = 00000.f;
  p = -1.f;
  MAX_RETRY = 3;

  BLOCK_SIZE = block_size;
  MAX_BLOCK = num_blocks;

  srand((unsigned int)(time(0)));

  fp = fopen(filename, "r+b");

  if(fp == NULL){
    printf("Could not open %s\n\n", filename);
    return -1;
  }
  return 0;
}

int read_blocks(int start_address, int nblocks, void * buffer){
  int i, j, e, s;
  e = 0;
  s = 0;

  void * blockRead = (void *) malloc(BLOCK_SIZE);

  if(start_address + nblocks > MAX_BLOCK){
    printf("out of bounds error\n");
    return -1;
  }

  fseek(fp, start_address * BLOCK_SIZE, SEEK_SET);

  for(int i = 0; i < nblocks; i++){
    usleep(L);
    s++;
    fread(blockRead, BLOCK_SIZE, 1, fp);

    for(j = 0; j < BLOCK_SIZE; j++){
      memcpy(buffer+(i*BLOCK_SIZE), blockRead, BLOCK_SIZE);
    }
  }

  free(blockRead);

  if(e == 0){
    return s;
  }
  else {
    return e;
  }
}

int write_blocks(int start_address, int nblocks, void * buffer){
  int i, e, s;
  e = 0;
  s = 0;

  void * blockWrite = (void *) malloc(BLOCK_SIZE);

  if(start_address + nblocks > MAX_BLOCK){
    printf("out of bounds error\n");
    exit(0);
    return -1;
  }

  fseek(fp, start_address * BLOCK_SIZE, SEEK_SET);

  for(int i = 0; i < nblocks; i++){
    usleep(L);

    memcpy(blockWrite, BLOCK_SIZE, 1, fp);

    fwrite(blockWrite, BLOCK_SIZE, 1, fp);
    fflush(fp);
    s++;
  }
  free(blockWrite);

  if(e == 0){
    return s;
  }
  else {
    return e;
  }

}
