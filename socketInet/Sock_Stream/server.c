#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include<string.h>
void showError(char *path)
{
    printf("error : %s\n", strerror(errno));
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
int main(){
    //TODO:
    return 0;
}