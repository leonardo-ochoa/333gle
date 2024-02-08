/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include "SocketUtil.h"

#define BUF 256

// Error usage message for the client to see
// Arguments:
// - prog_name: Name of the program
void Usage(char* progname);

int main(int argc, char** argv) {
  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    close(listen_fd);
    return EXIT_FAILURE;
  }

  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);
  int client_fd = accept(listen_fd,
                          reinterpret_cast<struct sockaddr*>(&caddr),
                          &caddr_len);
  if (client_fd < 0) {
    std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
    close(listen_fd);
    return EXIT_FAILURE;
  }

  unsigned char readbuf[BUF];
  while (1) {
    int read = WrappedRead(client_fd, readbuf, BUF);
    if (read == 0)  // eof
      break;
    if (read < 0) {  // error
      close(client_fd);
      close(listen_fd);
      return EXIT_FAILURE;
    }

    int write = WrappedWrite(1, readbuf, read);
    if (write != read) {  // error
      close(client_fd);
      close(listen_fd);
      return EXIT_FAILURE;
    }
  }

  // Close up shop.
  close(client_fd);
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}
