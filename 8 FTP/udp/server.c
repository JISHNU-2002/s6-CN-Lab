#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define max 1024

void recieve_file(struct sockaddr_in client,int s_sock){
    char buf[max];
    FILE *fp;
    char *filename = "server.txt";
    fp = fopen(filename,"w");
    if(fp == NULL){
        perror("[-]error in file operation\n");
        exit(0);
    }
    int m = sizeof(client);

    while(1){
        int n = recvfrom(s_sock,buf,max,0,(struct sockaddr*)&client,&m);
        if(strcmp(buf,"end") == 0){
            perror("[-]end of file\n");
            break;
        }
        printf("[+]recieving data : %s",buf);
        fprintf(fp,"%s",buf);
        bzero(buf,max);
    }

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

    int b = bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        perror("[-]UDP socket bind error\n");
        exit(0);
    }else{
        printf("[+]UDP socket bind success\n");
    }
    printf("[+]server ready\n\n");
    
    recieve_file(client,s_sock);
    printf("\n[+]file transfer complete\n");

    printf("[-]client disconnected\n");
    close(s_sock);
    return 0;
}