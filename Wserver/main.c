#include "global.h"
#include "params.h"



int main(int argc, char *argv[])
{
    fflush(stdout);
    // Starting control
    printf("[INFO] - Checking and registering params ...\n");
    sleep(1);
    if (!check_params(argc, argv)) {
        return 0;
    }

    // DDW Init
    // DepDataWeather *list_data = NULL;

    // Connect to socket REQ
    zsock_t *req = zsock_new(ZMQ_REQ);
    zsock_set_identity(req, "wserver");
    zsock_connect(req, "tcp://%s:%s", IP, REQPORT);

    // Connect to sockets PUB
    zsock_t *chat_srv_socket = zsock_new(ZMQ_PUB);
    zsock_bind(chat_srv_socket, "tcp://*:%s", PUBPORT);

    int i = 0;

    // Processus
    while (!zsys_interrupted) {

        // Send req msg to router
        zstr_sendf(req, "france");
        // if (VERBOSE == 1) { printf("SEND REQUEST ...\n"); }

        // Recv message from router
        char *message = zstr_recv(req);
        char *tmp = message;
        char *line;
        const char eol[2] = "\n";

        // Parse CSV Lines
        line = strtok(tmp, eol);

        // Insert all CSV lines in Chain List
        while( line != NULL ) {
            // printf("%s\n", line);
            zstr_sendf(chat_srv_socket, "%s", line);
            usleep(1000);
            // list_data = insert_ddw(list_data, );
            line = strtok(NULL, eol);
        }
        // if (VERBOSE == 1) { printf("RESPONSE : %s\n\n", message);}
        zstr_free(&message);
        i++;
        sleep(5);
    }
    printf("\e[1;1H\e[2J");
    printf("Server ");
    printfc("stopped \n", "red");
    zsock_destroy(&chat_srv_socket);
    zsock_destroy(&req);
    return 0;
}
