#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define max 1024

void send_file(struct sockaddr_in server,int s_sock){
    char buf[max];
    FILE *fp;
    char *filename = "client.txt";
    fp = fopen(filename,"r");
    if(fp == NULL){
        perror("[-]error in file operation\n");
        exit(0);
    }
    
    int m = sizeof(server);
    while(fgets(buf,max,fp) != NULL){
        int n = sendto(s_sock,buf,max,0,(struct sockaddr*)&server,m);
        if(n < 0){
            perror("[-]error in sending file\n");
            exit(0);
        }
        printf("[+]sending data : %s",buf);
        bzero(buf,max);
    }

    strcpy(buf,"end");
    sendto(s_sock,buf,max,0,(struct sockaddr*)&server,m);
    fclose(fp);
    return;
}

int main(){
    struct sockaddr_in server,client;
    int s_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(s_sock < 0){
        perror("[-]UDP socket error\n");
        exit(0);
    }else{
        printf("[+]UDP socket created\n");
    }
    server.sin_family = AF_INET;
    server.sin_port = 9000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("[+]client ready\n\n");

    send_file(server,s_sock);
    printf("\n[+]file transfer complete\n");

    printf("[-]client disconnected\n");
    close(s_sock);
    return 0;
}