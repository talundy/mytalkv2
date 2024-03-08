#include "mytalk_funcs.h"

void perrorUsage(){
    fprintf(stderr, "Usage: ./mytalk [-v] [-a] [-N] [hostname] port\n");
    exit(EXIT_FAILURE);
}
void parseArgs(int argc, char *argv[], char *flag_mask){
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            *flag_mask |= v_FLAG;
        } else if (strcmp(argv[i], "-a") == 0) {
            *flag_mask |= a_FLAG;
        } else if (strcmp(argv[i], "-N") == 0) {
            *flag_mask |= N_FLAG;
        } else {
            break;
        }
    }
}

uint32_t getAddress(char *hostname){
    struct addrinfo hints, *ai;
    uint32_t result = 0;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    if(getaddrinfo(hostname, NULL, &hints, &ai) == 0){
        if(ai)
            result = ((struct sockaddr_in *)ai->ai_addr)->sin_addr.s_addr;
        freeaddrinfo(ai);

    } else {
        perror("getaddrinfo in getAddress failed");
        exit(EXIT_FAILURE);
    }
    return result;
}

void chat(int sockfd){
    int done, len;
    char buf[BUFSIZE];
    struct pollfd fds[REMOTEHOST + 1];
    done = 0;

    fds[LOCALHOST].fd = STDIN_FILENO;
    fds[LOCALHOST].events = POLLIN;
    fds[LOCALHOST].revents = 0;

    fds[REMOTEHOST] = fds[LOCALHOST];
    fds[REMOTEHOST].fd = sockfd;

    do{
        poll(fds, sizeof(fds)/sizeof(struct pollfd), -1);
        if(fds[LOCALHOST].revents & POLLIN){
            len = (int)read(STDIN_FILENO, buf, BUFSIZE);
            send(sockfd, buf, len, 0);
        }
        if(fds[REMOTEHOST].revents & POLLIN){
            len = (int)recv(sockfd, buf, BUFSIZE, 0);
            write(STDOUT_FILENO, buf, len);
        }
        if(!strncmp(buf, "quit", 4))
            done = 1;
    } while (!done);
}
