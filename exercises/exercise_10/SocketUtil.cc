/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2@uw.edu
#include "SocketUtil.h"

#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

#include <iostream>

using std::cerr;
using std::endl;

bool LookupName(char* name,
                unsigned short port,
                struct sockaddr_storage* ret_addr,
                size_t* ret_addrlen) {
  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  int retval = getaddrinfo(name, nullptr, &hints, &results);
  if (retval != 0) {
    cerr << "getaddrinfo failed: " << gai_strerror(retval) << endl;
    return false;
  }
  if (results->ai_family == AF_INET) {
    struct sockaddr_in* v4addr =
        reinterpret_cast<struct sockaddr_in*>(results->ai_addr);
    v4addr->sin_port = htons(port);
  } else if (results->ai_family == AF_INET6) {
    struct sockaddr_in6* v6addr =
        reinterpret_cast<struct sockaddr_in6*>(results->ai_addr);
    v6addr->sin6_port = htons(port);
  } else {
    cerr << "getaddrinfo failed to provide an IPv4 or IPv6 address";
    cerr << endl;
    freeaddrinfo(results);
    return false;
  }
  assert(results != nullptr);
  memcpy(ret_addr, results->ai_addr, results->ai_addrlen);
  *ret_addrlen = results->ai_addrlen;
  freeaddrinfo(results);
  return true;
}

bool Connect(const struct sockaddr_storage& addr,
             const size_t& addrlen,
             int* ret_fd) {
  int socket_fd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    std::cerr << "socket() failed: " << strerror(errno) << std::endl;
    return false;
  }
  int res = connect(socket_fd, reinterpret_cast<const sockaddr*>(&addr),
                    addrlen);
  if (res == -1) {
    std::cerr << "connect() failed: " << strerror(errno) << std::endl;
    return false;
  }
  *ret_fd = socket_fd;
  return true;
}

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  int res = 0;
  while (1) {
    res = read(fd, buf, readlen);
    if (res == -1) {
      if (errno != EINTR && errno != EAGAIN) {
        return -1;
      }
      continue;
    }
    break;
  }
  return res;
}

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
  int res = 0;
  while (1) {
    res = write(fd, buf, writelen);
    if (res == -1) {
      if (errno != EINTR && errno != EAGAIN) {
        return -1;
      }
      continue;
    }
    break;
  }
  return res;
}
