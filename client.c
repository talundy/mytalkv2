#include "client.h"

void openClient(char *hostname, char *port, char flag_mask){
/*-----------------------STEP ONE: GET ADDRESS INFO -----------------------*/
    struct sockaddr_in serv_addr;
    uint32_t address;
    int sockfd, portnum;

    /* Convert hostname string to integer */
    portnum = (int)strtol(port, NULL, 10);
    if(portnum < 0 || portnum > 65535){
        fprintf(stderr, "Invalid port number\n");
        exit(EXIT_FAILURE);
    }

    /* Get address */
    address = getAddress(hostname);

/*-----------------------STEP TWO: CREATE SOCKET -----------------------*/
    /* Create socket file descriptor */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if(flag_mask & v_FLAG){
        printf("Socket created\n");
    }

/*-----------------------STEP THREE: CONNECT TO SERVER -----------------------*/
    /* Set up server address */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);
    serv_addr.sin_addr.s_addr = address;

    /* Connect to server */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    if(flag_mask & v_FLAG){
        printf("Connected to server\n");
    }

/*-----------------------STEP FOUR: SEND AND RECEIVE DATA -----------------------*/
    chat(sockfd);

/*-----------------------STEP FIVE: CLOSE SOCKET -----------------------*/
    close(sockfd);
    if(flag_mask & v_FLAG){
        printf("Socket closed\n");
    }
}