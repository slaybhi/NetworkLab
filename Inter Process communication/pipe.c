#include<stdio.h>
#include<unistd.h>

static int myCompare(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp((const char*)a, (const char*)b); 
} 



void main(int argc, char const *argv[])
{
	//creating pipes
	int pipefd[2];
	int returnstatus;
	int pid,i;
	char writemessage[4][20]={"arun","abhijith","zendeya","bharat"};
	char readmessage[4][20];
	returnstatus = pipe(pipefd);
	if (returnstatus==-1){
		printf("the pipe cannot be accessed.... there's an error in connnection\n");
	}

//creating the child process

	pid = fork();

//for child process
	if(pid==0)
	{
		for(i=0;i<4;i++){
		read(pipefd[0],readmessage[i],sizeof(readmessage[i]));
		}
		printf("sorted message from child\n");
		qsort(readmessage, 4, sizeof(const char[20]), myCompare);

		for(i=0;i<4;i++){
			printf("message %d %s\n",i,readmessage[i]);
		}
	}

//for parent process
	else 
	{	
		printf("writing to pipe by parent:\n");
		for(i=0;i<4;i++){
		printf("message %d %s\n",i, writemessage[i]);
		write(pipefd[1],writemessage[i],sizeof(writemessage[i]));
		}
	}

	return;
}