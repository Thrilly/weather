#include "global.h"
#include "params.h"



int main(int argc, char *argv[])
{
    fflush(stdout);
    // Starting control
    printf("[INFO] - Starting server ...\n");
    sleep(1);
    if (!check_params(argc, argv)) {
        return 0;
    }

    // DDW Init
    // DepDataWeather *list_data = NULL;

    // Connect to socket REQ
    zsock_t *socket_req = zsock_new(ZMQ_REQ);
    zsock_set_identity(socket_req, "wserver");
    zsock_connect(socket_req, "tcp://%s:%s", IP, REQPORT);

    // Connect to sockets PUB
    zsock_t *socket_pub = zsock_new(ZMQ_PUB);
    zsock_bind(socket_pub, "tcp://*:%s", PUBPORT);

    // Processus
    while (!zsys_interrupted) {

        // Send socket_req msg to router
        zstr_sendf(socket_req, "france");

        // Recv message from router
        char *message = zstr_recv(socket_req);
        char* tmp = message;
        char *line;
        char *str;
        const char eol[2] = "\n";

        // Parse CSV Lines
        line = strtok_r(tmp, eol, &str);

        // Insert all CSV lines in Chain List
        if (VERBOSE == 1) printf("### Receive from weather server ###\n");
        while( line != NULL ) {
            if (VERBOSE == 1) printf("%s\n", line);
            zstr_sendf(socket_pub, "%s", line);
            // list_data = insert_ddw(list_data, str);
            line = strtok_r(NULL, eol, &str);
            usleep(1000);
        }
        if (VERBOSE == 1)  printf("#### Sended to socket, end cycle, wait for 5sec ###\n");
        sleep(5);
    }
    printf("\e[1;1H\e[2J");
    printf("Server ");
    printfc("stopped \n", "red");
    zsock_destroy(&socket_pub);
    zsock_destroy(&socket_req);
    return 0;
}
