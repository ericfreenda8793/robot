#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define N 101
int bal=0;
long long ans=0;

void part(int length,int cur,char a[N]){
if(cur==length){
    return;
}
else if(a[cur]=='('){
      bal+=1;
        }
        else{
            bal-=1;
            if(a[cur-1]=='('){
                ans+=1*pow(2,bal);
               }
        }

        part(length,cur+1,a);



}


int main()
{
    int n;
    scanf("%d",&n);
    char arr[N];
    scanf("%s",arr);
    part(n,0,arr);
    printf("%lld",ans);

    return 0;
}
