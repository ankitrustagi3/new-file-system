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

typedef struct FileAccessStatus {
	int opened;
	int wr_ptr;
	int rd_ptr;
} FileAccessStatus;

typedef struct FileDescriptor {
	char filename[32];
	int fat_index;
	time_t timestamp;
	int size;
  FileAccessStatus fas;
} FileDescriptor;

typedef struct DirectoryDescriptor {
	FileDescriptor table[max_files];
	int count;
} DirectoryDescriptor;

typedef struct fat_node {
	size_t db_index;
	int next;
	int free;
} fat_node;

typedef struct FileAllocationTable {
	fat_node table[MAX_DISK];
	int count;
} FileAllocationTable;

typedef struct freeblocklist {
	int list[MAX_DISK];
} freeblocklist;

typedef union DiskBlock {
	DirectoryDescriptor dd;
	FileAllocationTable fat;
	freeblocklist fbl;
} DiskBlock;

void makefs(int fresh);
void sfs_ls();
int sfs_open(char * name);
int sfs_close(int fileID);
int sfs_write(int fileID, char * buf, int length);
int sfs_read(int fileID, char* buf, int length);

#endif
