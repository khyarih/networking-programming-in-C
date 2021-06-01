#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include<string.h>
void showError(char * fct,char *path)
{
    printf("%s \n ", fct);
    printf("error : %s\n", strerror(errno));
    if(strcmp("",path)!=0)
        unlink(path);
    exit(0);
}
int main(){
    int _socket,size,_bind,_recvfrom,_sendto,_otherSideSize;
    char msg[100];
    struct sockaddr_un sockaddr_un_s,sockaddr_un_c;
    struct sockaddr *sockaddr_s = (struct sockaddr *)&sockaddr_un_s,
                    *sockaddr_c = (struct sockaddr *)&sockaddr_un_c;

    //socket
    _socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(_socket < 0)
        showError("socket","");
    
    //ServerSocket
    sockaddr_un_s.sun_family = AF_UNIX;
    strcpy(sockaddr_un_s.sun_path,"/home/arch/exam/socketUnix/Sock_Dgram/serverSocket");
    
    //ClientSocket
    sockaddr_un_c.sun_family = AF_UNIX;
    strcpy(sockaddr_un_c.sun_path,"/home/arch/exam/socketUnix/Sock_Dgram/clientSocket");

    //bind
    _bind = bind(_socket, sockaddr_c, sizeof(sockaddr_un_c));
    if(_bind < 0)
        showError("bind",sockaddr_un_c.sun_path);

    //sendto
    strcpy(msg, "hello server");
    _sendto = sendto(_socket,msg,100,0,sockaddr_s,sizeof(sockaddr_un_s));
    if(_sendto <0)
        showError("sendto",sockaddr_un_c.sun_path);

    //recvfrom
    _recvfrom = recvfrom(_socket, msg, 100, 0, sockaddr_s, &_otherSideSize);
    if(_recvfrom < 0)
        showError("recvfrom",sockaddr_un_c.sun_path);
    printf("%s\n", msg);

    unlink(sockaddr_un_c.sun_path);
    return 0;
}