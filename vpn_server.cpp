#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <stdarg.h>
#include <netdb.h>
#include "helpers.h"
#include "server.h"

int main(int argc, char* argv[]) 
{
  int socket_fd = 0;

  // Open server connection
  auto *self = new server();
  self->createConnection();
  socket_fd = self->getSocket();

  char buffer[BUFFLEN];
  getchar();
  while (1)
  {
      // Read an IP packet from a client
      ssize_t count = recvfrom(socket_fd, buffer, BUFFLEN, 0, (struct sockaddr *) &self->serv, &self->serv_size);
      dump_packet(count, buffer);
  }

  return 0;
}