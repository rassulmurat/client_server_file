//
// Created by user on 29.9.16.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//#define THREAD

void *connection_handler(void*);

int main()
{
    int socket_desc = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(19951);
    bind(socket_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(socket_desc, 10);
    while (1) {
        printf("Waiting for user\n");
        connfd = accept(socket_desc, (struct sockaddr*)NULL, NULL);
        if (connfd >= 0) {
#ifdef THREADS
            pthread_t thr;
            pthread_create(&thr,NULL,connection_handler,(void *) &connfd);
#else
            pid_t pid = fork();
            puts("process created");
            if (pid == 0) {
                Connection_handler(&connfd);
		        return 0;
            }
#endif
        }
    }
}

void *connection_handler(void *socket_desc)
{
    printf("User connected\n");
    int socket = *(int*)socket_desc;
    //recieve massage from the user
    char usrmsg[2000];
    recv(socket,usrmsg,sizeof(usrmsg),0);
    puts(usrmsg);
    FILE *fl = fopen(usrmsg,"r");
    int size = 10;
    char rd_loc[size];
    unsigned int last = 1;
    while (1) {
        fgets(rd_loc,size,fl);
        ssize_t ret = send(socket,rd_loc,(size_t)size,0);
        if (ret != size) {
            usleep(1);
        }
        if (feof(fl)) {
            printf("End of the file\n");
            break;
        }
    }
    close(socket);
    printf("Socket closed\n");
#ifdef THREADS
    pthread_exit(NULL);
#endif
}
