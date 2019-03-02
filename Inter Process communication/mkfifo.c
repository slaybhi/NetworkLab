#include <stdio.h>  
#include <fcntl.h> 
#include <unistd.h> 



static int myCompare(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp((const char*)a, (const char*)b); 
} 

int main(){
	int fd, i, retstat;
	int p;
	char writenames[4][20]={"aman","abhijith","zendeya","rawn"};
	char readnames[4][20];
	char * myfifo = "/tmp/myfifo";
	
	retstat = mkfifo(myfifo, 0666);

	if(retstat < 0)
		perror("mkfifo fail");

//creating child process
		p = fork();

		//fork fails
		if (p<0){
			printf("fork failed.... cannot create the child process\n");
			return 0;
		}


//for parent process

	else if (p>0){
		fd = open(myfifo, O_WRONLY);
		for ( i = 0; i < 4; ++i)
		{
			write (fd,writenames[i],sizeof(writenames[i]));
		}
		
		close(fd);
		wait(0);
	}


//for child process
	else{
		wait(0);
		fd = open(myfifo, O_RDONLY);
		for ( i = 0; i < 4; ++i)
		{
			read(fd,readnames[i],sizeof(readnames[i]));
		}
		
				
		qsort(readnames, 4, sizeof(const char[20]), myCompare);

		for (i = 0; i < 4; ++i)
		{
			printf("%s\n",readnames[i]);
		}
		exit(0);
		
	}
	unlink(myfifo);
}