#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

void showError(char *fct)
{
    printf("%s\n", fct);
    printf("error : %s\n", strerror(errno));
    exit(0);
}

void readMsg(char *msg, int nbr)
{
    printf("(%d) new Msg >>> ", nbr);
    scanf("%s", msg);
}

void writeMsg(char *msg, int nbr)
{
    printf("(%d) Msg: %s\n", nbr, msg);
}
int main()
{
    int _socket, _bind, _sendto, _recvfrom,size;
    char msg[100];
    struct sockaddr_in sockaddr_in;

    //socket
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (_socket < 0)
        showError("socket");

    //bind
    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(6000);
    sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    _bind = bind(_socket, (struct sockaddr *)&sockaddr_in, sizeof(sockaddr_in));
    if (_bind < 0)
        showError("bind");

    //recvfrom
    _recvfrom = recvfrom(_socket, msg, sizeof(msg), 0, (struct sockaddr *)&sockaddr_in, &size);
    if (_recvfrom < 0)
        showError("bind");
    writeMsg(msg, 0);

    //sendto
    strcpy(msg, "hello client");
    _sendto = sendto(_socket, msg, sizeof(msg), 0, (struct sockaddr *)&sockaddr_in, sizeof(sockaddr_in));
     if (_sendto < 0)
        showError("sendto");

    printf("the end");
    return 0;
}