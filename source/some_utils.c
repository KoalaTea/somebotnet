/*
*	some_utils.c
*
*/

#include "../include/some_hds.h"

void daemonize(){
	daemon_pid = fork();
	if(daemon_pid){
		exit(EXIT_SUCCESS);
	}
}
void error(char *msg){
	perror(msg);
	exit(0);
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    //     // from here on,
    //         //    tmp points to the end of the result string
    //             //    ins points to the next occurrence of rep in orig
    //                 //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
   
    if (!result)
        return NULL;
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    free(tmp); //questionquestion
    return result;
}

void changetoinst(char * initinfo){

	getinst = malloc(strlen(ccinstruct)-strlen("init.php")+strlen("instructions.php")-strlen("Iamagreatcookie")+strlen(cookie));
        getinst = str_replace(ccinstruct, "Iamagreatcookie", cookie);
	getinst = str_replace(getinst, "init.php", "instructions.php");
}
