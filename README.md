# myVSFS
This project is oriented around creating a VSFS (Very Simple File System). The simple functions that are included in this repository are:

**sfs_write()**
This functionality of this method is to write to the file system. 

**sfs_read()**
This function is responsible for reading in the data from the file.

**sfs_open()**
This function is responsible for opening the file located in the system.  

**sfs_close()**
This function is put into the file system to close any file that has already been opened in the file system.  


### Minor Problem
There is a segmentation error that pops up when the files are read through a second time. I believe that the cause of this error is due to the fact that the pointer passes through all of the files and is never reset. Therefore, once the second call is made using the for-loop, then pointer goes beyond the scope of the data provided for the file system and returns the error. 
