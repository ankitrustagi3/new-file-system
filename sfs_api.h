#include "disk_emu.h"
#include "sfs_header.h"

DirectoryDescriptor root;
FileAllocationTable fat;

static int open_files = 0;

void makefhs(int fresh){
         if(fresh)
}
