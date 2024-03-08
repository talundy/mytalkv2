#include "mytalk_funcs.h"
#include "client.h"
#include "server.h"



int main(int argc, char *argv[]) {
/*-----------------------STEP ONE: HANDLE ARGUMENTS-----------------------*/
    char flag_mask = 0;
    /* Check number of arguments */
    if (argc < 2 || argc > 6) {
        perrorUsage();
    }
    /* Get flags */
    parseArgs(argc, argv, &flag_mask);

/*-------------------------- STEP TWO: BRANCH --------------------------*/

    /* If the second to last argument is not a flag,
     * the it is the hostname. Extract and pass to client mode. */

    char *port;
    if(argv[argc-2][0] != '-' && argc > 2) {
        char *hostname;
        hostname = argv[argc-2];
        port = argv[argc-1];
        openClient(hostname, port, flag_mask);
    } else if(argv[argc-1][0] != '-') {
        port = argv[argc-1];
        openServer(port, flag_mask);
    } else {
        /* This should be handled in parseArgs,
         * but redundancies never hurt anyone. */
        perrorUsage();
    }





  return 0;
}


