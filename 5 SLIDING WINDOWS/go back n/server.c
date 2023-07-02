#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/time.h>

int main(){
    int server_sock,client_sock;
    struct sockaddr_in server,client;
    int n = sizeof(client);
    char buf[1024];

    server_sock = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_port = 6000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(server_sock < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP server socket created\n");
    }

    int b = bind(server_sock,(struct sockaddr*)&server,sizeof(server));
    if(b < 0){
        printf("[-]Bind error\n");
        exit(0);
    }else{
        printf("[+]Bind successfull\n");
    }

    listen(server_sock,10);
    printf("[+]server listening waiting for client\n");
    client_sock = accept(server_sock,(struct sockaddr*)&client,&n);
    if(client_sock < 0){
        printf("[-]client connection error\n");
        exit(0);
    }else{
        printf("[+]client connection accepted\n");
    }

    char msg[50] = "server : ack";
    int flag1=1,flag2=1,i;
    for(i=0;i<10;i++){
        flag1 = 1;
        bzero(buf,sizeof(buf));
        if(i==8 && flag2==1){
            printf("here/simulating loss\n");
            flag2=0;
            read(client_sock,buf,sizeof(buf));
        }

        read(client_sock,buf,sizeof(buf));
        if(buf[strlen(buf)-1] != i+'0'){
            printf("\ndiscarded as out of order\n");
            i--;
        }else{
            printf("%s\n",buf);
            printf("ack-%d send\n",i);
            strcpy(buf,msg);
            buf[(strlen(buf))] = i+'\0';
            write(client_sock,buf,sizeof(buf));
        }
    }

    close(client_sock);
    printf("[-]client disconnected\n");
    close(server_sock);
    return 0;
}
