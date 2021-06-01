#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void showError(char *fct, char *path)
{
    printf("%s\n", fct);
    printf("error : %s\n", strerror(errno));
    if (strcmp("", path))
        unlink(path);
    exit(0);
}
void readMsg(char *msg)
{
    printf(" new Msg >>> ");
    scanf("%s", msg);
}
void writeMsg(char *msg)
{
    printf(" Msg: %s\n", msg);
}
int main()
{
    int _socket, _bind, _listen, _connect, size;
    char msg[100];
    struct sockaddr_un sockaddr_un_s;
    struct sockaddr *sockaddr_s = (struct sockaddr *)&sockaddr_un_s;

    //socket
    _socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (_socket < 0)
        showError("socket", "");

    //bind
    sockaddr_un_s.sun_family = AF_UNIX;
    strcpy(sockaddr_un_s.sun_path, "/home/arch/exam/socketUnix/Sock_Stream/serverSocket");

    //connect
    _connect = connect(_socket, sockaddr_s, sizeof(sockaddr_un_s));
    if (_connect < 0)
        showError("connect", "");

    // //write
    // strcpy(msg, "hello server");
    // if (write(_socket, msg, sizeof(msg)) < 0)
    //     showError("read", "");
    // //read
    // if(read(_socket,msg,sizeof(msg)) < 0)
    //     showError("read", "");
    // printf("%s\n", msg);
    while (1)
    {
        //write
        readMsg(msg);
        if (write(_socket, msg, sizeof(msg)) < 0)
            showError("read", "");
        if(strcmp("exit",msg)==0)
            break;
        //read
        if (read(_socket, msg, sizeof(msg)) < 0)
            showError("read", "");
        writeMsg(msg);
        if(strcmp("exit",msg)==0)
            break;
    }

    return 0;
}