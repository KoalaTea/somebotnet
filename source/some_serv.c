/*
*	some_serv.c
*
*/

#include "../include/some_hds.h"

int connect_cc(sock_t *sp){
	
	sp->s_fd = false;
	sp->s_hs = gethostbyname(server);

	if(sp->s_hs == NULL){
		error("No such host");
	}

	sp->s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sp->s_fd < 0){
		error("ERROR opening socket");
	}
	sp->s_addr.sin_family = AF_INET;
	sp->s_addr.sin_port = htons(theport);
	sp->s_addr.sin_addr = *((struct in_addr *)sp->s_hs->h_addr);
	
	memset(sp->s_addr.sin_zero, '\0', sizeof(sp->s_addr.sin_zero));
	
	if (connect(sp->s_fd, (struct sockaddr *)&sp->s_addr, sizeof(sp->s_addr)) == false){
		error("FAILED HARCORE MAN");
		return EXIT_FAILURE;
	}
	
	htmlconnect(sp);
	close(sp->s_fd);
	
	return EXIT_SUCCESS;
	
}

int htmlconnect(sock_t *sp){

        int tmpres;
        char buf[BUFSIZ+1];
	int sent = 0;
	while(sent < strlen(ccinstruct)){
		tmpres = send(sp->s_fd, ccinstruct+sent, strlen(ccinstruct)-sent, 0);
		if(tmpres == -1){
			error("Can't send query");
			return EXIT_FAILURE;
		}
		sent += tmpres;
	}
	
	memset(buf, 0, sizeof(buf));
	int htmlstart =0;
	char * htmlcontent;
	char * html;
	while((tmpres = recv(sp->s_fd, buf, BUFSIZ, 0)) > 0){
		if(htmlstart == 0){
			htmlcontent = strstr(buf, "\r\n\r\n");
			if(htmlcontent != NULL){
				htmlstart = 1;
				htmlcontent += 4;
			}
		}else{
			htmlcontent = buf;
		}
		if(htmlstart){
			fprintf(stdout, htmlcontent);
		}

		html = (char *) malloc(strlen(htmlcontent));
                strcpy(html, htmlcontent);
		memset(buf, 0, tmpres);

		changetoinst(html);
		
	}
	if(tmpres<0){
		error("Error recieving data");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

char* instruct(sock_t *sp){

	sp->s_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sp->s_fd < 0){
                error("ERROR opening socket");
        }

	if (connect(sp->s_fd, (struct sockaddr *)&sp->s_addr, sizeof(sp->s_addr)) == false){
                error("FAILED HARCORE MAN2?");
                return "";
        }
	int tmpres;
        char buf[BUFSIZ+1];
        int sent = 0;

	//char *requestinst = ccinstruct;

	printf("%s",getinst);
        while(sent < strlen(getinst)){
                tmpres = send(sp->s_fd, getinst+sent, strlen(getinst)-sent, 0);
                if(tmpres == -1){
                        error("Can't send query");
                        return "";
                }
                sent += tmpres;
        }

        memset(buf, 0, sizeof(buf));
        int htmlstart =0;
        char * htmlcontent;
	char * html = "test";
        while((tmpres = recv(sp->s_fd, buf, BUFSIZ, 0)) > 0){
                if(htmlstart == 0){
                        htmlcontent = strstr(buf, "\r\n\r\n");
                        if(htmlcontent != NULL){
                                htmlstart = 1;
                                htmlcontent += 4;
                        }
                }else{
                        htmlcontent = buf;
                }
                if(htmlstart){
                	fprintf(stdout, htmlcontent);
		}
		
		instruction = (char *) malloc(strlen(htmlcontent));
		strcpy(instruction, htmlcontent);
                memset(buf, 0, tmpres);
        }
        if(tmpres<0){
                error("Error recieving data");
                return "";
        }
	close(sp->s_fd);
	//char *temp;
	//strcpy(temp, htmlcontent);
        //return temp;
        return html;
/*
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    *//* Create file where data will be stored *//*
    FILE *fp;
    fp = fopen("sample_file.txt", "w");
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    *//* Receive data in chunks of 256 bytes *//*
    while((bytesReceived = read(sp->s_fd, recvBuff, 256)) > 0)
    {
        printf("Bytes received %d\n",bytesReceived);    
        //recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        //printf("%s \n", recvBuff);
    }
    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
    fclose(fp);
    return "okay";
*/
}
