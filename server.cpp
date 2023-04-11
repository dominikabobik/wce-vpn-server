#include "server.h"

server::server()
{
    socket_fd = 0;
    serv_size = sizeof(serv);
    bzero((char *) &serv, serv_size);
    from_size = sizeof(from);
    bzero((char *) &from, from_size);
}

int server::createConnection()
{
    int error = 0;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1)
    {
        printf("Error while creating socket\n");
        error = socket_fd;
        return error;
    }

    printf("Socket fd: %d\n", socket_fd);
    bzero((char *) &serv, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    fflush(stdout);
    // Binding socket
    serv_size = sizeof(serv);
    error = ::bind(socket_fd, (struct sockaddr *) &serv, serv_size);
    if (error < 0)
    {
        printf("Failed to bind the socket\n");
        close(socket_fd);
        return error;
    }

    printf("+----------------------------------------\n");
    printf("| Server running\n");
    printf("| Port:       %d (network byte order)\n", serv.sin_port);
    printf("|             %d (hostorder)\n", PORT);
    printf("| Domain:     AF_INET\n");
    printf("| Protocol:   UDP\n");
    printf("+----------------------------------------\n");

    return error;
}

int server::getSocket() {
    return socket_fd;
}

