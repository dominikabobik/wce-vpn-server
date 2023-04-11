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

#define BUFFLEN (4 * 1024)

const char HEX[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'a', 'b', 'c', 'd', 'e', 'f',
};

int has_ports(int protocol);

void dump_ports(int protocol, int count, const char *buffer);

void hex(char *source, char *dest, ssize_t count);

void dump_packet_ipv4(int count, char *buffer);

void dump_packet_ipv6(int count, char *buffer);

void dump_packet(int count, char *buffer);