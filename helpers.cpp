#include "helpers.h"

int has_ports(int protocol)
{
  switch(protocol) {
  case IPPROTO_UDP:
  case IPPROTO_TCP:
    return 1;
  default:
    return 0;
  }
}

void dump_ports(int protocol, int count, const char* buffer)
{
  if (!has_ports(protocol))
    return;
  if (count < 4)
    return;
  uint16_t source_port;
  uint16_t dest_port;
  memcpy(&source_port, buffer, 2);
  source_port = htons(source_port);
  memcpy(&dest_port, buffer + 2, 2);
  dest_port = htons(dest_port);
  fprintf(stderr, " sport=%u, dport=%d\n", (unsigned) source_port, (unsigned) dest_port);
}

void hex(char* source, char* dest, ssize_t count)
{
  for (ssize_t i = 0; i < count; ++i) {
    unsigned char data = source[i];
    dest[2 * i] = HEX[data >> 4];
    dest[2 * i + 1] = HEX[data & 15];
  }
  dest[2 * count] = '\0';
}

void dump_packet_ipv4(int count, char* buffer)
{
  if (count < 20) {
    fprintf(stderr, "IPv4 packet too short\n");
    return;
  }

  char buffer2[2*BUFFLEN + 1];
  hex(buffer, buffer2, count);

  int protocol = (unsigned char) buffer[9];
  struct protoent* protocol_entry = getprotobynumber(protocol);

  unsigned ttl = (unsigned char) buffer[8];

  fprintf(stderr, "IPv4: src=%u.%u.%u.%u dst=%u.%u.%u.%u proto=%u(%s) ttl=%u\n",
    (unsigned char) buffer[12], (unsigned char) buffer[13], (unsigned char) buffer[14], (unsigned char) buffer[15],
    (unsigned char) buffer[16], (unsigned char) buffer[17], (unsigned char) buffer[18], (unsigned char) buffer[19],
    (unsigned) protocol,
    protocol_entry == NULL ? "?" : protocol_entry->p_name, ttl
    );
  dump_ports(protocol, count - 20, buffer + 20);
}

void dump_packet_ipv6(int count, char* buffer)
{
  if (count < 40) {
    fprintf(stderr, "IPv6 packet too short\n");
    return;
  }

  char buffer2[2*BUFFLEN + 1];
  hex(buffer, buffer2, count);

  int protocol = (unsigned char) buffer[6];
  struct protoent* protocol_entry = getprotobynumber(protocol);

  char source_address[33];
  char destination_address[33];

  hex(buffer + 8, source_address, 16);
  hex(buffer + 24, destination_address, 16);

  int hop_limit = (unsigned char) buffer[7];

  fprintf(stderr, "IPv6: src=%s dst=%s proto=%u(%s) hop_limit=%i\n",
    source_address, destination_address,
    (unsigned) protocol,
    protocol_entry == NULL ? "?" : protocol_entry->p_name,
    hop_limit);
  dump_ports(protocol, count - 40, buffer + 40);
}

void dump_packet(int count, char* buffer)
{
  unsigned char version = ((unsigned char) buffer[0]) >> 4;
  if (version == 4) {
    dump_packet_ipv4(count, buffer);
  } else if (version == 6) {
    dump_packet_ipv6(count, buffer); 
  } else {
    fprintf(stderr, "Unknown packet version\n");
  }
}