#ifndef SFS_API_H
#define SFS_API_H

#include "disk_emu.h"
#include "sfs_header.h"
#include "sfs_utils.h"

DirectoryDescriptor root;
FileAllocationTable fat;
#Hello 
static int open_files = 0;

void makefhs(int fresh){
         if(fresh){
               init_fresh_disk("disks.sfs", sizeof(diskBlock), NB_BLOCK);

               FAT_init(&fat);
               DirectoryDescriptor_init(&root);

               write_blocks(0, 1, (void *) &root);
               write_blocks(1, 1, (void *) &fat);
         }
         else {
              init_disk("disks.sfs", sizeof(diskBlock), NB_BLOCK);
              read_blocks(0, 1, (void *) &root);
              read_blocks(1, 1, (void *) &fat);
         }
}

void sfs_ls(){
    printf("\n");

    for(int i = 0; i < MAX_FILE; i++){
        if(root.table[i].size > 0){
              int kb = root.table[i].size / 1024;
              char *tm = ctime(&root.table[i].filename);
              tm[24] = '\0';
              printf("%25s\t%dKB\t%s\n", tm, kb, root.table[i]);
        }
    }
}

int sfs_open(char * name){
    int fileID = getIndexOfFileInDirectory(name, &root);

    if(fileID != -1){
        return fileID;
    }

    fileID = open_files++;
    FileDescriptor_createFiles(name, &(root.table[fileID]));

    write_blocks(0, 1, (void *) &root);
    write_blocks(1, 1, (void *) &fat);

    return fileID;
}

int sfs_close(int fileID){

    if(open_files <= fileID){
          fprintf(stderr, "Error: file %d does not exist.", fileID);
          return -1;
    }

    root.table[fileID].fas.opened = 0;
    open_files--;
    return 0;
}

int sfs_write(int fileID, char * buf, int length){
    if(open_files <= fileID){
         fprintf(stderr, "Error: File #%d does not exist. \n", fileID);
         return 0;
    }

    int address = 2;

    for(int i = 0; i < length; i++){
         if(address != -1){
              write_blocks(address, 1, (void *) &buf[i]);
              root.table[fileID].size++;
         }
         else {
              fprintf(stderr, "Error: The disk is already full.\n");
              break;
         }
    }

    write_blocks(0, 1, (void *) &root);
    write_blocks(1, 1, (void *) &fat)

    return root.table[fileID].size;
}

int sfs_read(int fileID, char * buf, int length){
    if(open_files <= fileID && root.table[fileID].fas.opened == 0){
            fprintf(stderr, "No such file %d is opened/n", fileID);
            return 0;
    }
    buf = FAT_getPartFile(root.table[fileID], fat, length);
    return EOF;
}

#endif
