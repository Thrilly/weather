#include <czmq.h>

int main(int argc, char *argv[])
{
  if (argc < 4) {
    printf("ip address, port number and departement are mandatory\n");
    return 0;
  }
  zsock_t *client = zsock_new(ZMQ_SUB);
  zsock_connect(client, "tcp://%s:%s", argv[1], argv[2]);
  printf("\e[1;1H\e[2J");
  printf("Client connected to tcp://%s:%s\n", argv[1], argv[2]);

  // zsock_set_subscribe(client, argv[3]);
  zsock_set_subscribe(client, strcat(argv[3], ","));
  while (!zsys_interrupted) {
    char *message = zstr_recv(client);
    printf("\e[1;1H\e[2J");
    char *tmp = message;
    char *line;

    const char virg[2] = ",";

    // Parse CSV Lines
    line = strtok(tmp, virg);
    int i = 0;
    // Insert all CSV lines in Chain List
    while( line != NULL ) {
        if (i == 0) {
            printf("zipcode : %s\n", line);
        } else if (i == 1) {
            printf("name : %s\n", line);
        } else if (i == 2) {
            printf("weather : %s\n", line);
        } else if (i == 3) {
            printf("temp : %sC\n", line);
        }
        line = strtok(NULL, virg);
        i++;
    }
    zstr_free(&message);
  }

  zsock_destroy(&client);
  return 0;
}
