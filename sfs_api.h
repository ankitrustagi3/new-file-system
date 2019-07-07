#include "disk_emu.h"
#include "sfs_header.h"

DirectoryDescriptor root;
FileAllocationTable fat;

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
