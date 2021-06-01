#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include<string.h>
void showError(char * fct, char *path)
{
    printf("%s\n", fct);
    printf("error : %s\n", strerror(errno));
    if(strcmp("",path))
        unlink(path);
    exit(0);
}
int main(){
    int _socket,size,_bind,_recvfrom,_sendto,_otherSideSize,_socket_2;
    char msg[100];
    struct sockaddr_un sockaddr_un;
    struct sockaddr *sockaddr = (struct sockaddr *)&sockaddr_un;

    //socket
    _socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(_socket < 0)
        showError("socket","");

    //bind
    sockaddr_un.sun_family = AF_UNIX;
    strcpy(sockaddr_un.sun_path,"/home/arch/exam/socketUnix/Sock_Dgram/serverSocket");
    size = sizeof(sockaddr_un);
    _bind = bind(_socket, (struct sockaddr *)&sockaddr_un, size);
    if(_bind <0 )
        showError("bind1",sockaddr_un.sun_path);

    //recvfrom
    _recvfrom = recvfrom(_socket, msg, 100, 0, sockaddr, &_otherSideSize);
    if(_recvfrom < 0)
        showError("recvfrom",sockaddr_un.sun_path);
    printf("%s\n", msg);

    //sendto
    strcpy(msg, "hello client");
    _sendto = sendto(_socket,msg,100,0,sockaddr,_otherSideSize);
    if(_sendto <0)
        showError("sendto","");

    unlink("/home/arch/exam/socketUnix/Sock_Dgram/serverSocket");
    return 0;
}