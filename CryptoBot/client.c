#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 8192 /* Max text line length */

int open_clientfd(char *hostname, int port) {
  // The client's socket file descriptor.
  int clientfd;
  // serveraddr is used to record the server information (IP address
  // and port number).
  //
  // struct sockaddr_in {
  //   short            sin_family;   // e.g. AF_INET
  //   unsigned short   sin_port;     // e.g. htons(3490)
  //   struct in_addr   sin_addr;     // see struct in_addr, below
  //   char             sin_zero[8];  // zero this if you want to
  // };
  struct sockaddr_in serveraddr;

  printf("Echo Client is creating a socket.\n");

  // First, we create the socket file descriptor with the given
  // protocol and protocol family.
  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  // Record the protocol family we are using to connect.
  serveraddr.sin_family = AF_INET;

  // Convert the port from host byte order to network byte order and
  // store this in the server address structure.
  serveraddr.sin_port = htons(port);
  serveraddr.sin_addr.s_addr = inet_addr(hostname);

  printf("Echo Client is trying to connect to (%s:%d).\n", inet_ntoa(serveraddr.sin_addr), serveraddr.sin_port);

  // Establish a connection with the server.
  if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

  printf("Echo Client connected.\n");

  // Return the connected file descriptor.
  return clientfd;
}

int main(int argc, char **argv) {
  // The client socket file descriptor.
  int clientfd;
  // The port number.
  int port;
  // Variable to store the host/server domain name.
  char *host;
  // A buffer to receive data from the server.
  char buf[MAXLINE];
  char* id;
  // First, we check the program arguments:
  if (argc != 4) {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }

  // First argument is host, second is port:
  id = argv[1];
  port = atoi(argv[2]);
  host = argv[3];

  // Open the client socket file descriptor given the host and port:
  clientfd = open_clientfd(host, port);
  char* spire = "cs230 HELLO abhinitgiri@umass.edu\n";
  send(clientfd, spire, strlen(spire), 0);

  int iter = (rand() % 300) + 2000;

  for (int i = 0; i < iter; i++) {
    memset(buf, 0, MAXLINE);
    recv(clientfd, buf, MAXLINE - 1, 0);
    // Remove the newline from fgets:
    buf[strcspn(buf, "\n")] = '\0';
    int first_cipher_index = 13;
    int start_of_message = first_cipher_index + 27;

    int message_size = 0;
    int j = start_of_message; 
    while (buf[j] >= 97 && buf[j] <= 122) {
        message_size++;
        j++;
    }
    
    char* decryp_message = (char*)(malloc(sizeof(char) * (message_size + 1)));
    for (int k = 0, s = start_of_message; k < message_size; k++, s++) { 
        int index = buf[s] - 97;
        decryp_message[k] = buf[first_cipher_index + index];
    }
    decryp_message[message_size + 1] = '\n';
    char final[message_size + 8];
    sprintf(final, "cs230 %s\n", decryp_message);

    send(clientfd, final, strlen(final), 0);
    free(decryp_message);
    memset(final, 0, message_size + 7);
    // free(sub_cipher);
  }
  memset(buf, 0, MAXLINE);
  recv(clientfd, buf, MAXLINE - 1, 0);
  // Close the file descriptor:
  close(clientfd);
  exit(0);
}