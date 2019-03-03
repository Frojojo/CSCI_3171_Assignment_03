// Program to create server

// To do:
// UNIX
// Memsets?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int port, listenSockFD, acceptSockFD, clientLen;
  char buffer[256];
  struct sockaddr_in serverAddr, clientAddr; // using netinet/in.h

  // Error handling: if missing port number
  if (argc < 2)
  {
    fprintf(stderr, "Error: Missing port number. Enter port number in intial args.\n");
    exit(1);
  }
  port = atoi(argv[1]); // converting port entry to int

  // setting fields for serverAddr
  bzero((char *) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET; // UNIX?
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  // UNIX?
  // creating new socket for listening
  listenSockFD = socket(AF_INET, SOCK_STREAM, 0);

  // error handling: if the socket cannot be opened
  if (listenSockFD == -1)
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }

  // binding socket to address
  if (bind(listenSockFD,
      (struct sockaddr *) &serverAddr,
      sizeof(serverAddr)) == -1)
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }

  // listening for connection
  if (listen(listenSockFD, 5) == -1) // error handling not necessary here
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }

  // accept new connection
  clientLen = sizeof(clientAddr);
  acceptSockFD = accept(listenSockFD, (struct sockaddr *) &clientAddr, clientLen);
  if (acceptSockFD == -1) // error handing: if connection unsuccessful
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }

  // reading from socket
  bzero(buffer, 256);
  if (read(acceptSockFD, buffer, 255) == -1) // if read is unsuccessful
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }
  printf("This is where the game starts!");

  // writing to socket
  if(write(acceptSockFD, "???", 3) == -1)
  {
    fprintf(stderr, "Error %d: %s.\n", errno, strerror(errno));
    exit(1);
  }


  return 0;
}