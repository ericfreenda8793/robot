#include <stdio.h>
#include <stdlib.h>

int data[2000][4]; //0 for start index 1 for end index
int list[10000000];
int sortlist[2000][2]; //0 for sorting value 1 for index

void bubblesort(int list[2000][2],int amount){
int temp1,temp2;
for(int i=0;i<amount-1;i++){
    for(int j=0;j<amount-1-i;j++){
        if(list[j][0]<list[j+1][0]){
            temp1=list[j][0];
            temp2=list[j][1];
            list[j][0]=list[j+1][0];
            list[j][1]=list[j+1][1];
            list[j+1][0]=temp1;
            list[j+1][1]=temp2;
        }
        else if(list[j][0]==list[j+1][0]){
            // printf("swap %d %d\n",data[list[j][1]][3],data[list[j+1][1]][3]);
           if(data[list[j][1]][3]<data[list[j+1][1]][3]){
            temp2=list[j][1];
            list[j][1]=list[j+1][1];
            list[j+1][1]=temp2;
           }
           else if(data[list[j][1]][3]==data[list[j+1][1]][3]){
           //printf("fuckkk %d %d\n",data[list[j][1]][2],data[list[j+1][1]][2]);
            if(data[list[j][1]][2]<data[list[j+1][1]][2]){

            temp2=list[j][1];
            list[j][1]=list[j+1][1];
            list[j+1][1]=temp2;
            }
           }
        }
    }
}

}
int main()
{
   int times;
   scanf("%d",&times);
   for(int i=0;i<times;i++){
    int group;
    scanf("%d",&group);
    int indexcount=0;
    int gnc;

    for(int j=0;j<group;j++){
       scanf("%d",&gnc);
       //for data j
       data[j][2]=gnc;
       int total=0;
       int max=0;
        for(int k=0;k<gnc;k++){
            scanf("%d",list+indexcount+k);
            total+=list[indexcount+k];
            if(list[indexcount+k]>max){
                max=list[indexcount+k];
            }
        }
        data[j][3]=max;
        sortlist[j][0]=total;
        sortlist[j][1]=j;

       data[j][0]=indexcount;
       indexcount+=gnc;
       //data[j][1]= indexcount-1;
    }
bubblesort(sortlist,group);
    for(int j=0;j<group;j++){
        for(int k=0;k<data[sortlist[j][1]][2];k++){
                if(k==data[sortlist[j][1]][2]-1){
                    printf("%d\n",list[data[sortlist[j][1]][0]+k]);
                }
                else{
                 printf("%d ",list[data[sortlist[j][1]][0]+k]);
                }
        }
    }
   }
return 0;
}
