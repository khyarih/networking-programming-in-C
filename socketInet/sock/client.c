#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

void showError(char* fct)
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
int main(){
    int _socket, _bind, _sendto, _recvfrom,size;
    char msg[100];
    struct sockaddr_in sockaddr_in_s,sockaddr_in_c;

    //socket
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(_socket < 0)
        showError("socket");

    //init sockaddr_in_s
    sockaddr_in_s.sin_family = AF_INET;
    sockaddr_in_s.sin_port = htons(6000);
    sockaddr_in_s.sin_addr.s_addr = inet_addr("127.0.0.1");

    //bind
    //init socketaddr_in_client
    sockaddr_in_c.sin_family = AF_INET;
    sockaddr_in_c.sin_port = htons(8000);
    sockaddr_in_c.sin_addr.s_addr = inet_addr("127.0.0.1");

    _bind = bind(_socket, (struct sockaddr *)&sockaddr_in_c, sizeof(sockaddr_in_c));
    if(_bind < 0)
        showError("bind");

    //sendto
    strcpy(msg, "hello server");
    _sendto = sendto(_socket, msg, sizeof(msg), 0, (struct sockaddr *)&sockaddr_in_s, sizeof(sockaddr_in_s));
    if(_sendto < 0)
        showError("sendto");

    //recvfrom
    _recvfrom = recvfrom(_socket, msg, sizeof(msg), 0, (struct sockaddr *)&sockaddr_in_s, &size);
    if(_recvfrom < 0)
        showError("recvfrom");
    writeMsg(msg,0);

    printf("the end");
    return 0;
}