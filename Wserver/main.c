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

    // Players Init
    // DepDataWeather *list_data;
    // list_data = NULL;

    // Connect to socket REQ
    zsock_t *req = zsock_new(ZMQ_REQ);
    zsock_set_identity(req, "wserver");
    zsock_connect(req, "tcp://%s:%s", IP, REQPORT);

    // Connect to sockets PUB
    zsock_t *chat_srv_socket = zsock_new(ZMQ_PUB);
    zsock_bind(chat_srv_socket, "tcp://*:%s", PUBPORT);



    // Processus
    while (!zsys_interrupted) {
        zstr_sendf(req, "france");
        if (VERBOSE == 1) { printf("SEND REQUEST ...\n"); }

        char *message = zstr_recv(req);
        if (VERBOSE == 1) { printf("RESPONSE : %s\n\n", message);}
        zstr_free(&message);

        zstr_sendf(chat_srv_socket, "#all: %s\n", "TEST");
        sleep(2);
    }
    printf("\e[1;1H\e[2J");
    printf("Server ");
    printfc("stopped \n", "red");
    zsock_destroy(&chat_srv_socket);
    zsock_destroy(&req);
    return 0;
}
