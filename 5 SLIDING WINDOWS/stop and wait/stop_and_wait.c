#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int i,j,t,packet[50],fsize;
    fsize = (rand()%16)+1;
    printf("frame size = %d\n",fsize);
    printf("   timeout = ");
    scanf("%d",&t);
    printf("\nframe\t data\twtime\tackn\tresend\n");

    for(i=0;i<fsize;i++){
        packet[i] = rand()%100;
        printf("%d\t %d\t",i+1,packet[i]);

        while(j=0 || rand()%2==0){
            sleep(1);
            printf("1");
            sleep(1);
            for(j=2 ;rand()%2==0 && j<4; j++){
                printf("-%d",j);
                sleep(1);
            }
            if(j>=(t+1)){
                printf("\tNO \tRESEND\n%d\t %d\t",i+1,packet[i]);
            }else{
                break;
            }
        }
        if(j==0){
                sleep(1);
                printf("0");
        }
        printf("\tYES \tNO\n");
    }
    return 0;
}