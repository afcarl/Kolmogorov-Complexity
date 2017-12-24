#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define MAXPENDING 5 /* Max connection requests */
#define BUFFSIZE 65536
void Die(char *mess)
{
    perror(mess);
    exit(1);
}

FILE* fin;
char buffer[BUFFSIZE];
void HandleClient(int sock)
{
    int received = -1, read;
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
    {
        Die("Failed to receive initial bytes from client");
    }
    fin = fopen("input5.txt", "rb");
    if (received > 0)
    {
        while ((read = fread(buffer, 1, BUFFSIZE-1, fin)) > 0) {
            buffer[read] = 0;
            send(sock, buffer, read, 0);
        }
        // if (send(sock, buffer, received, 0) != received)
        // {
        //     Die("Failed to send bytes to client");
        // }
        // if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0)
        // {
        //     Die("Failed to receive additional bytes from client");
        // }
    }
    fclose(fin);
    close(sock);
}


int main(int argc, char *argv[])
{
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        Die("Failed to create socket");
    }
    memset(&echoserver, 0, sizeof(echoserver));
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
    echoserver.sin_port = htons(atoi(argv[1]));
    if (bind(serversock, (struct sockaddr *)&echoserver,
             sizeof(echoserver)) < 0)
    {
        Die("Failed to bind the server socket");
    }
    if (listen(serversock, MAXPENDING) < 0)
    {
        Die("Failed to listen on server socket");
    }
    while (1)
    {
        unsigned int clientlen = sizeof(echoclient);
        if ((clientsock =
                 accept(serversock, (struct sockaddr *)&echoclient,
                        &clientlen)) < 0)
        {
            Die("Failed to accept client connection");
        }
        fprintf(stdout, "Client connected: %s\n", inet_ntoa(echoclient.sin_addr));
        HandleClient(clientsock);
    }
    return 0;
}
