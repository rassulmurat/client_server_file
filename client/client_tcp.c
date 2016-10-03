//
// Created by user on 30.9.16.
//
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

void *connect_client()
{
    int socket_desc = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(123456);

    if (connect(socket_desc , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) < 0)
    {
        puts("Connect error");
    }else{
        puts("Connected to serv");
        static char dest[] = "/home/user/github/client_server_file/tcp_serv.c";
        if(send(socket_desc,&dest,sizeof(dest),0)<0)
        {
            puts("Sending request failed");
        }else{
            puts("Request sent");
        }
        char serv_msg[4000];
        while(1)
        {
            int rcv = recv(socket_desc, serv_msg , sizeof(serv_msg),0);
            if(rcv <0)
            {
                puts("recieve failed");
                pthread_exit(NULL);
            }else
            {
                if(rcv == 0){
                    puts("File Finished");
                    pthread_exit(NULL);
                }else{
//                    puts("pack recieved");
                    printf(serv_msg);
                }
            }

        }
    }
}
