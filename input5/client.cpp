#include <stdio.h>
#include <winsock.h>
#include <stdlib.h>
FILE*fout;
void output(char*buf, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 128; j; j/=2) {
            putc("01"[(j&buf[i])>0], fout);
        }
}

#define RCVBUFSIZE 65536
int main(int argc, char *argv[])
{
    fout = fopen("r.txt", "w");
    int sock;           
    struct sockaddr_in echoServAddr;
    unsigned short echoServPort;    
    char *servIP;                   
    char *echoString;               
    char echoBuffer[RCVBUFSIZE];    
    int echoStringLen;              
    int bytesRcvd, totalBytesRcvd;  
    WSADATA wsaData;                
    servIP = argv[1];             
    echoString = argv[2];         

    if (argc == 4)
        echoServPort = atoi(argv[3]);
    else
        echoServPort = 7;  

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
    {
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family      = AF_INET;        
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port        = htons(echoServPort);
    connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr));

    echoStringLen = strlen(echoString);         

    send(sock, echoString, echoStringLen, 0);

    totalBytesRcvd = 0;
    while (true)
    {
        (bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0));
        totalBytesRcvd += bytesRcvd; 
        if (bytesRcvd == 0) break;
        output(echoBuffer, bytesRcvd);
    }

    fclose(fout);
    closesocket(sock);
    WSACleanup();  

    exit(0);
}