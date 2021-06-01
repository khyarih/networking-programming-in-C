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
    if (strcmp("", path) != 0)
        unlink(path);
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
    int _socket, _bind, _listen, _newSocket, size, PID, nbr = 0;
    char msg[100];
    struct sockaddr_un sockaddr_un_s, sockaddr_un_c;
    struct sockaddr *sockaddr_s = (struct sockaddr *)&sockaddr_un_s,
                    *sockaddr_c = (struct sockaddr *)&sockaddr_un_c;

    //socket
    _socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (_socket < 0)
        showError("socket", "");

    //bind
    sockaddr_un_s.sun_family = AF_UNIX;
    strcpy(sockaddr_un_s.sun_path, "/home/arch/exam/socketUnix/Sock_Stream/serverSocket");
    _bind = bind(_socket, sockaddr_s, sizeof(sockaddr_un_s));
    if (_bind < 0)
        showError("bind", sockaddr_un_s.sun_path);

    //listen
    _listen = listen(_socket, 3);
    if (_listen < 0)
        showError("listen", sockaddr_un_s.sun_path);

    //accept
    while (1)
    {
        nbr++;
        _newSocket = accept(_socket, sockaddr_c, &size);
        if (_newSocket < 0)
            showError("accept", sockaddr_un_s.sun_path);

        PID = fork();
        if (PID <= 0)
        {
            while (1)
            {
                //read
                if (read(_newSocket, msg, sizeof(msg)) < 0)
                    showError("read", sockaddr_un_s.sun_path);
                writeMsg(msg, nbr);
                if(strcmp("exit",msg)==0)
                    close(_newSocket);

                //write
                readMsg(msg, nbr);
                if (write(_newSocket, msg, sizeof(msg)) < 0)
                    showError("read", sockaddr_un_s.sun_path);
                if(strcmp("exit",msg)==0)
                    close(_newSocket);
            }
            break;
        }
    }

    return 0;
}