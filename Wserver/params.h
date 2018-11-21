#define WAIT_BEFORE_START_SERVER 1


char REQPORT[]  = "4242";
char PUBPORT[]  = "4243";
char IP[]       = "localhost";
int VERBOSE     = 0;

int check_params(int argc, char *argv[])
{
    for (int i = 1; i < argc; i= i+2) {

        // *********** PUB PORT ***********
        if (strcmp(argv[i],"--pub-port") == 0 || strcmp(argv[i],"-pp") == 0) {
            if (argv[i+1] != NULL) { // control if params value exist
                if (atoi(argv[i+1]) > 0 && atoi(argv[i+1]) < 65535) { // control data validity
                    strcpy(PUBPORT, argv[i+1]); // assing params
                } else { // else print error
                    printfc("[FAIL] - Unable runing server : Invalid port, must be integer beetween 1 and 65535\n", "red");
                    return 0;
                }
            } else { // else print error
                printfc("[FAIL] - PUB Port number is expected after pub-port parameter\n", "red");
                return 0;
            }
        // *********** END PUB PORT ***********

        // *********** REQ PORT ***********
        } else if (strcmp(argv[i],"--req-port") == 0 || strcmp(argv[i],"-rp") == 0) {
            if (argv[i+1] != NULL) { // control if params value exist
                if (atoi(argv[i+1]) > 0 && atoi(argv[i+1]) < 65535) { // control data validity
                    strcpy(REQPORT, argv[i+1]); // assing params
                } else { // else print error
                    printfc("[FAIL] - Unable runing server : Invalid port, must be integer beetween 1 and 65535\n", "red");
                    return 0;
                }
            } else { // else print error
                printfc("[FAIL] - REQ Port number is expected after req-port parameter\n", "red");
                return 0;
            }
        // *********** END REQ PORT ***********


        // *********** IP ***********
        } else if(strcmp(argv[i],"--ip") == 0 || strcmp(argv[i],"-i") == 0) {
            if (argv[i+1] != NULL) { // control if params value exist
                strcpy(IP, argv[i+1]); // assing params
            } else { // else print error
                printfc("[FAIL] - IP is expected after ip parameter\n", "red");
                return 0;
            }
        // *********** END IP ***********

        // *********** VERBOSE ***********
        } else if(strcmp(argv[i],"--verbose") == 0 || strcmp(argv[i],"-v") == 0) {
            VERBOSE = 1;
            i--;
        // *********** END VERBOSE ***********


        // *********** INVALID PARAMETER ***********
        } else {
            printfc("[FAIL] - Unable running server : Unknow parameter ", "red");
            printfc(argv[i], "blue");
            printf("\n");
            return 0;
        }
        // *********** END INVALID PARAMETER ***********
    }

    // *********** PRINT INFOS ***********


    if (VERBOSE == 1) {
        printf("[INFO] - Verbose mode actived\n");
        usleep(100000);
        printf("[INFO] - Serveur socket ROUTER listenning on tcp://%s:%s \n", IP, REQPORT);
        usleep(100000);
        if (atoi(REQPORT) < 1000) {
            printfc("[WARN] - It\'s recommanded to use port higher than 1000 for socket ROUTER\n", "yellow");
            usleep(100000);
        }
        printf("[INFO] - Serveur socket PUB listenning on tcp://*:%s \n", PUBPORT);
        usleep(100000);
        if (atoi(PUBPORT) < 1000) {
            printfc("[WARN] - It\'s recommanded to use port higher than 1000 for socket PUB\n", "yellow");
            usleep(100000);
        }

        printfc("[SUCC] - Server is ready ! Starting server \n", "green");
        for (int i = 0; i < WAIT_BEFORE_START_SERVER; i++) {
            printfc(".\n", "green");
            sleep(1);
        }
        printf("\e[1;1H\e[2J");
        printf("Server is");
        printfc(" running \n", "green");

    }
    return 1;
}
