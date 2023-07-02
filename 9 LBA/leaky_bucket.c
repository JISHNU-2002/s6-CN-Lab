#include<stdio.h>
#include<stdlib.h>

struct packet{
    int time;
    int size;
}p[50];

int main(){
    int i,j,k=0,n,bucket_size,outgoing_rate,bucket_present=0;
    printf("Enter No of packets = ");
    scanf("%d",&n);
    printf("Enter bucket size   = ");
    scanf("%d",&bucket_size);
    printf("Enter outgoing rate = ");
    scanf("%d",&outgoing_rate);
    printf("\nEnter packet details\n");
    for(i=0;i<n;i++){
        printf("\npacket[%d] arraival time = ",i);
        scanf("%d",&p[i].time);
        printf("packet[%d] size            = ",i);
        scanf("%d",&p[i].size);
    }

    int m = p[n-1].time;
    i=1;
    while(i<=m || bucket_present !=0){
        printf("time = %d\n",i);
        if(p[k].time == i){
            bucket_present = bucket_present + p[k].size;
            printf("%d byte inserted\n",p[k].size);
            k++;
        }else{
            printf("%d byte packet discarded\n",p[k].size);
            k++;
        }
        if(bucket_present == 0){
            printf("no packet transmition\n");
        }else if(bucket_present >= outgoing_rate){
            bucket_present = bucket_present - outgoing_rate;
            printf("%d bytes inserted\n",outgoing_rate);
        }else{
            printf("%d bytes inserted\n",bucket_present);
            bucket_present = 0;
        }
        printf("%d bytes in bucket\n",bucket_present);
    }
    return 0;
}