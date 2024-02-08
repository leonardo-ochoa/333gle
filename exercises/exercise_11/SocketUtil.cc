/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include "SocketUtil.h"

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <iostream>

using std::cerr;
using std::endl;


int Listen(char* portnum, int* sock_family) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_flags |= AI_V4MAPPED;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  struct addrinfo* result;
  int res = getaddrinfo(nullptr, portnum, &hints, &result);
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  int listen_fd = -1;
  for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
    listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_fd == -1) {
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      listen_fd = -1;
      continue;
    }
    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));
    if (bind(listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      *sock_family = rp->ai_family;
      break;
    }
    close(listen_fd);
    listen_fd = -1;
  }
  freeaddrinfo(result);
  if (listen_fd == -1) {
    return listen_fd;
  }
  if (listen(listen_fd, SOMAXCONN) != 0) {
    std::cerr << "Failed to mark socket as listening: ";
    std::cerr << strerror(errno) << std::endl;
    close(listen_fd);
    return -1;
  }
  return listen_fd;
}

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  int res;
  while (1) {
    res = read(fd, buf, readlen);
    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
    }
    break;
  }
  return res;
}

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
  int res, written_so_far = 0;
  while (written_so_far < writelen) {
    res = write(fd, buf + written_so_far, writelen - written_so_far);
    if (res == -1) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
      break;
    }
    if (res == 0)
      break;
    written_so_far += res;
  }
  return written_so_far;
}
