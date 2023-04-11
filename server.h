#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <vector>

#ifndef CHATAPP_SERVER_H
#define CHATAPP_SERVER_H

#define PORT 55555

using namespace std;

class server {
private:

public:
    server();
    int createConnection();
    int getSocket();
    int socket_fd;
    struct sockaddr_in serv;
    socklen_t serv_size;
    struct sockaddr_in from;
    socklen_t from_size;
};

#endif //CHATAPP_SERVER_H
