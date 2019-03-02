#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	//initialising the pipe 
	int pipefd1[2], pipefd2[2] ,pid,returnstatus1, returnstatus2;
	char pipe1writemessage[20] = "hi", pipe2writemessage[20] = "there";
	char readmessage[20];

	//connecting and checking the pipes
	returnstatus1 = pipe(pipefd1);

	if(returnstatus1 ==-1)
		printf("error in connecting to pipe 1\n");

	returnstatus2 = pipe(pipefd2);

	if(returnstatus2 ==-1)
		printf("error occured in connecting to 2nd pipe\n");


	//creating child process 

	pid = fork();

//child process 

	if(pid==0){
		//..close the unwnted pipes
		close(pipefd1[1]); 
      	close(pipefd2[0]);
      	read(pipefd1[0],readmessage,sizeof(readmessage));
      	printf("the message arrived in child process : %s\n",readmessage);
     
     	// writing to parent 

      	printf("In Child: Writing to pipe 2 – Message is %s\n", pipe2writemessage);
      	write(pipefd2[1], pipe2writemessage, sizeof(pipe2writemessage));
	}	


	//parent process 

	else{

		//clode unwanted pipe ends
		close(pipefd1[0]);
		close(pipefd2[1]);
		printf("In parent: wrinting to pipe 1 - message is %s\n",pipe1writemessage);
		write(pipefd1[1],pipe1writemessage,sizeof(pipe1writemessage));


		//reading in parent
		
		read(pipefd2[0],readmessage,sizeof(readmessage));
		printf("the message that is read from parent %s\n", readmessage);
		

	}


	return 0;
}