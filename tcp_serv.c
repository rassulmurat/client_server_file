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

void *Connection_handler(void*);

void *createSocket()
{
    int socket_desc = 0, connfd = 0, *new_con;
    struct sockaddr_in serv_addr;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(123456);

    bind(socket_desc, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(socket_desc, 10);

    while(1)
    {
        printf("Waiting for user\n");
        connfd = accept(socket_desc, (struct sockaddr*)NULL, NULL);
        if(connfd>0 || connfd == 0)
        {
            pthread_t thr;
            *new_con = connfd;
#ifdef THREADS
            pthread_create(&thr,NULL,Connection_handler,(void *) new_con);
#else
            Connection_handler(new_con);
#endif
        }
    }
}

void *Connection_handler(void* socket_desc)
{
    int socket = *(int*)socket_desc;
    printf("User connected\n");
    //recieve massage from the user
    char usrmsg[2000];
    recv(socket,usrmsg,sizeof(usrmsg),0);
    puts(usrmsg);
    FILE* fl = fopen(usrmsg,"r");
    size_t size = 10;
    char rd_loc[size];
    unsigned int last = 1;
    while (1)
    {
//        fread(rd_loc,sbytes,numelem*sbytes,fl);
        fgets(rd_loc,size,fl);
        int ret = send(socket,rd_loc,size,0);
        if(ret != 40)
        {
            usleep(1);
        }
        if(feof(fl)){
            printf("End of the file\n");
            break;
        }
    }
    close(socket);
    printf("Socket closed\n");
    pthread_exit(NULL);
}