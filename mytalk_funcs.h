#ifndef MYTALK_MYTALK_FUNCS_H
#define MYTALK_MYTALK_FUNCS_H

/* For cleanliness */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>

/* Flags */
#define v_FLAG  1
#define a_FLAG  2
#define N_FLAG  4

#define LOCALHOST 0
#define REMOTEHOST 1

/* Buffer size */
#define BUFSIZE 1024

/* Print usage, throw error */
void perrorUsage();
/* Parse flags */
void parseArgs(int argc, char *argv[], char *flag_mask);
/* Get the name of the machine */
uint32_t getAddress(char *hostname);
/* Chat with the other user */
void chat(int sockfd);



#endif
