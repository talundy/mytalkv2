#include "server.h"

#define BACKLOG 100


void openServer(char *port, char flag_mask){
/*-----------------------STEP ONE: CREATE SOCKET-----------------------*/
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*-----------------------STEP TWO: ATTACH ADDRESS-----------------------*/
    /* IPv4 */
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(strtol(port, NULL, 10));
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1){
        perror("bind in openServer failed");
        exit(EXIT_FAILURE);
    }

    if(flag_mask & v_FLAG){
        printf("Socket created and attached to port %s\n", port);
    }

/*---------------------STEP THREE: WAIT FOR CONNECTION---------------------*/
    if(listen(sockfd, BACKLOG) == -1){
        perror("listen in openServer failed");
        exit(EXIT_FAILURE);
    }
    if(flag_mask & v_FLAG){
        printf("Server is listening for connections on port %s\n", port);
    }

/*-----------------------STEP FOUR: ACCEPT CONNECTION-----------------------*/

    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);
    int client_fd;
    while(1){
        printf("Waiting for connection...\n");

        /* Connect to client */
        client_fd = accept(sockfd, (struct sockaddr *)&client, &client_size);
        if(client_fd == -1){
            perror("accept in openServer failed");
            exit(EXIT_FAILURE);
        }

        /* Get IP address of client */
        const char *ip = inet_ntop(AF_INET,
                                   &client.sin_addr,
                                   (char *)malloc(INET_ADDRSTRLEN),
                                   INET_ADDRSTRLEN);
        if(ip == NULL){
            perror("inet_ntop in openServer failed");
            exit(EXIT_FAILURE);
        }
        /* Get port # of client */
        int clientPort = ntohs(client.sin_port);
        /* Get name of client */
        struct hostent *client_ent = gethostbyaddr(&client.sin_addr, sizeof(client.sin_addr), AF_INET);
        if(flag_mask & v_FLAG){
            printf("New connection from %s:%d\n", ip, clientPort);
        }



        /* Check if we should accept the connection */
        if(flag_mask & a_FLAG){
            /* accept all connections */;
        } else {
            printf("Mytalk request from %s.   ", client_ent->h_name);
            printf("Accept? (y/n) ");
            if(getchar() != 'y'){
                /* Shut everything down */
                close(client_fd);
                close(sockfd);
                exit(EXIT_SUCCESS);
            }
        }


        if(flag_mask & v_FLAG){
            printf("Accepted connection from client\n");
        }

        /* Send and receive data */
        chat(client_fd);
        close(client_fd);
        close(sockfd);
        exit(EXIT_SUCCESS);
    }

}