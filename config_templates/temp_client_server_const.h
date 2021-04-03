/**
 * NOTE: This is a template file. Please do the following:
 *    - copy this file into the 'tcp_controller' directory
 *    - rename the file to remove the "temp_" at the beginning
 *    - update the definitions below with values that work with your setup
 */

/* This file defines constants used in the TCP client/server files used as a possible control scheme for the cat laser turret. */

#define DEBUG 0 /* Enable debug messages. */

#define PORT  1 /* The port used for the TCP socket connection. */
#define SERVER_IP "127.0.0.1" /* IPv4 address used for the TCP server and client connection. */

#define BUFFER_SIZE 2048 /* The size of information being sent to, and read from the server */
