#ifndef __SOME_SERV_H_
#define __SOME_SERV_H_

pid_t daemon_pid;

typedef struct
{
  int s_fd;
  struct hostent *s_hs;
  struct sockaddr_in s_addr;
} sock_t;

#endif
