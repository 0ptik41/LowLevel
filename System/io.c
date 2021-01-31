#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>

/* function go check whether a file exists. */
bool exists(const char *path){
	// Try to open file
	FILE *fptr = fopen(path, "r");

	// If file does not exists 
	if (fptr == NULL)
		return false;

	// File exists hence close file and return true.
	fclose(fptr);

	return true;
}

/*function to get size of the file.*/
long int getSize(const char *file_name){
	struct stat st; /*declare stat variable*/
	 
	/*get the size using stat()*/
	if(stat(file_name,&st)==0)
		return (st.st_size);
	else
		return -1;
}

/* shows file permissions (taken from example) */
void sfile(char const filename[]){

  struct stat sfile;

  if(stat(filename,&sfile)==-1){
	printf("Error Occurred\n");
  }

  //Accessing data members of stat struct
  printf("\nFile st_uid %d \n",sfile.st_uid);
  printf("\nFile st_blksize %ld \n",sfile.st_blksize);
  printf("\nFile st_gid %d \n",sfile.st_gid);
  printf("\nFile st_blocks %ld \n",sfile.st_blocks);
  printf("\nFile st_size %ld \n",sfile.st_size);
  printf("\nFile st_nlink %u \n",(unsigned int)sfile.st_nlink);
  printf("\nFile Permissions User\n");
  printf((sfile.st_mode & S_IRUSR)? "r":"-");
  printf((sfile.st_mode & S_IWUSR)? "w":"-");
  printf((sfile.st_mode & S_IXUSR)? "x":"-");
  printf("\n");
  printf("\nFile Permissions Group\n");
  printf((sfile.st_mode & S_IRGRP)? "r":"-");
  printf((sfile.st_mode & S_IWGRP)? "w":"-");
  printf((sfile.st_mode & S_IXGRP)? "x":"-");
  printf("\n");
  printf("\nFile Permissions Other\n");
  printf((sfile.st_mode & S_IROTH)? "r":"-");
  printf((sfile.st_mode & S_IWOTH)? "w":"-");
  printf((sfile.st_mode & S_IXOTH)? "x":"-");
  printf("\n");
}

/* read contents of a file into a char buffer */
void readFile(const char *file_name, char dataOut[]){
	if(!exists(file_name))
		return;
	long int filesize;
	filesize = getSize(file_name);
	// read into intermediate buffer
	char buf[filesize];
	memset(buf, '\0', sizeof(buf));
	FILE *file;
	size_t nread;

	file = fopen(file_name, "r");
	if (file){
		while((nread = fread(buf, 1, sizeof buf, file)) > 0)
			strcpy(dataOut, buf);
		if (ferror(file)){
			printf("Error Reading: %s\n", file_name);
		}
		fclose(file);
	}
}

/* execute system command and return the value */
void execute(char *command, char dataOut[]){
    // execute command and pipe output to file 
    system(strcat(command, " >> cmd.txt"));
    // read file and destroy it
    long int res = getSize("cmd.txt");
    if(res >= 0){
        readFile("cmd.txt", dataOut);
        remove("cmd.txt");
    } else {
        printf("Error Executing Command\n");
    }
}

void main(int argc, char *argv[]){
    
}