#ifndef SFS_API_UTIL
#define SFS_API_UTIL

char vd[100][30000];
int fatID = 0;

void FAT_init(){

}

int FAT_getFreeNode(){

}

void DirectoryDescriptor_init(DirectoryDescriptor * root){
  int i;
  for(i = 0; i < MAX_FILE_NAME_LENGTH; i++){
    root->table[i].size = EMPTY;
  }
}

void FileDescriptor_createFiles(char * name, FileDescriptor file){
  strcpy(file->filename, name);
  file->fas.opened = 1;
  file->fas.rd_ptr = 0;
  file->fas.wr_ptr = 0;
  file->size = 0;
  file->timestamp = time(NULL);
}

void VirtualDisk_write(int address, void * buff,int length){
  char * string = (char *) buff;
  vd[address][length] = '\0';
  strncpy(string, vd[address], length);
}

#endif
