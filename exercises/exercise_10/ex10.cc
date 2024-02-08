/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

#include "SocketUtil.h"
using std::cerr;
using std::endl;

#define BUF 1024

// Error usage message for the client to see
// Arguments:
// - prog_name: Name of the program
void Usage(char* progname);

int main(int argc, char** argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }

  int fd = open(argv[3], O_RDONLY);
  if (fd == -1) {
    cerr << "error opening file" << endl;
    return EXIT_FAILURE;
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure.
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage(argv[0]);
  }

  // Connect to the remote host.
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    Usage(argv[0]);
  }

  unsigned char readbuf[BUF];
  while (1) {
    int read = WrappedRead(fd, readbuf, BUF);
    if (read < 0) {
      close(fd);
      close(socket_fd);
      cerr << "read failed" << endl;;
      return EXIT_FAILURE;
    } else if (read == 0) {
      break;
    }
    int write = WrappedWrite(socket_fd, readbuf, read);
    if (write < 0) {
      close(fd);
      close(socket_fd);
      cerr << "read failed" << endl;;
      return EXIT_FAILURE;
    }
  }
  close(fd);
  close(socket_fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  cerr << "usage: " << progname << " hostname port local-file" << endl;
  exit(EXIT_FAILURE);
}
