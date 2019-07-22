#ifndef
	#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef SFS_API_HEADER
#define SFS_API_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_BLOCK 4096
#define MAX_DISK NB_BLOCK
#define FAT_SIZE NB_BLOCK

#define EMPTY -69
