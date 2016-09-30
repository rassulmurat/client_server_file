//
// Created by user on 29.9.16.
//
//#include <pthread.h>
#include "tcp_serv.c"
#include "client_tcp.c"

void *createSocket();
void *connect_client();

int main (void)
{
    pthread_t tserv;
    pthread_t tclient;
    pthread_create(&tserv,NULL,createSocket,NULL);
    sleep(1);
    pthread_create(&tclient,NULL,connect_client,NULL);
    sleep(5);
}

