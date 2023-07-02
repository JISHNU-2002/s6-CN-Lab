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
    int n = sizeof(server);
    char buf[1024];

    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0){
        printf("[-]TCP server socket error\n");
        exit(0);
    }else{
        printf("[+]TCP server socket created\n");
    }

    memset(&server,'\0',sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = 6000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("[+]client ready...\n");

    client_sock = connect(server_sock,(struct sockaddr*)&server,n);
    if(client_sock < 0){
        printf("[-]client connection error\n");
        exit(0);
    }else{
        printf("[+]client connection successfull\n");
        printf("[+]Server Up || Go back n (n=3) used to send 10 messages\n\n");

    }

    char msg[50] = "client : frame";
    time_t t1,t2;
    struct timeval timeout1,timeout2,timeout3;
    int rv1,rv2,rv3,flag=0,i=-1;
    fd_set set1,set2,set3;

    label1:
        i++;
        bzero(buf,sizeof(buf));
        strcpy(buf,msg);
        buf[(strlen(buf))] = i+'0';
        buf[(strlen(buf))] = '\0';
        printf("%s\n",buf);
        write(server_sock,buf,sizeof(buf));
        sleep(1);

        i++;
        bzero(buf,sizeof(buf));
        strcpy(buf,msg);
        buf[strlen(buf)] = i+'0';
        printf("%s\n",buf);
        write(server_sock,buf,sizeof(buf));
        i++;
        sleep(1);
    
    label2:
        bzero(buf,sizeof(buf));
        strcpy(buf,msg);
        buf[strlen(buf)] = i+'0';
        printf("%s\n",buf);
        write(server_sock,buf,sizeof(buf));
        FD_ZERO(&set1);
        FD_SET(server_sock,&set1);
        timeout1.tv_sec = 2;
        timeout2.tv_usec = 0;
        rv1 = select(server_sock+1,&set1,NULL,NULL,&timeout1);
        if(rv1 < 0){
            printf("\n[-]select error\n");
        }else if(rv1 == 0){
            printf("\nGOING BACK from %d || timeout\n",i);
            i = i-3;
            goto label1;
        }else{
            read(server_sock,buf,sizeof(buf));
            printf("%s\n",buf);
            
            if(i<=9){
                goto label2;
            }
        }

    label3:
        FD_ZERO(&set2);
        FD_SET(server_sock,&set2);
        timeout2.tv_sec = 3;
        timeout2.tv_usec = 0;
        rv2 = select(server_sock+1,&set2,NULL,NULL,&timeout2);
        if(rv2 < 0){
            printf("[-]select error\n");
        }else if(rv2 == 0){
            printf("\nGOING BACK from %d || timeout on last 2\n",i-1);
            i = i-2;
            bzero(buf,sizeof(buf));
            strcpy(buf,msg);
            buf[strlen(buf)] = i+'0';
            write(server_sock,buf,sizeof(buf));
            sleep(1);

            i++;
            bzero(buf,sizeof(buf));
            strcpy(buf,msg);
            buf[strlen(buf)] = i+'0';
            write(server_sock,buf,sizeof(buf));
            sleep(1);
            goto label3;
        }else{
            read(server_sock,buf,sizeof(buf));
            printf("%s\n",buf);
            bzero(buf,sizeof(buf));
            read(server_sock,buf,sizeof(buf));
            printf("%s\n",buf);
        }
    close(server_sock);
    printf("[-]disconnected from server\n");
    return 0;
}
