#include <iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
//using queue to store the entry
struct qnode{
int data;
int r;
int c;
qnode* next;
qnode* prev;
qnode(int d,int rr,int cc){
data = d;
r=rr;
c=cc;
next = NULL;
prev=NULL;
}
};

struct Queue{
qnode *front, *rear;
Queue(){
front = rear = NULL;
}

void enque(int x,int r,int c){
//create a new node
qnode *temp = new qnode(x,r,c);
//if queue is empty then new node is front and rear both
if(rear==NULL){
    front=rear=temp;
    return;
}

// add the new node at the end of the queue
//let the previous of temp be the previous of rear
temp->prev=rear;
rear->next=temp;
rear=temp;

}

void dfront(){
//if queue is empty. return NULL.
if(front==NULL)
    return;
//store previous front and move front one node ahead
qnode* temp = front;
front =front->next;
// If front becomes NULL,then change rear also as NULL
if(front==NULL)
    rear=NULL;

    delete(temp);

}

void dend(){
//if queue is empty. return NULL.
if(front==NULL)
    return;
//let rear point to the previous of rear
qnode* temp=rear;
rear=rear->prev;
rear->next=NULL;
delete(temp);

}


};

void go(char m[][1001],Queue &q,int boundr,int boundc,int counter);

int main()
{
    //create a queue to store the index of cell
     Queue q;
    char filename[50];
    ifstream eric;
    cin.getline(filename,50);
    eric.open(filename);


   if(!eric.is_open()){
    exit(EXIT_FAILURE);
   }
   //import row column battery life
   char mrowcol[50];
   eric>>mrowcol;
   //ger row
   int row = atoi(mrowcol);
   //get column
   eric>>mrowcol;
   int col = atoi(mrowcol);

   //get battery life
   char bat[50];
   eric>>bat;
  int batlife=atoi(bat);
   cout<<row<<" "<<col;
  cout<<"\n"<<batlife<<endl;
  //create the map
  char Map[1001][1001];
  //create a counter to count the total free cell
  int count=0;
   for(int i = 0;i<row;i++){
      eric>>Map[i];
      for(int j=0;j<col;j++){
        if(Map[i][j]=='0'){
            count++;
        }
        if(Map[i][j]=='R'){
            q.enque(0,i,j);
        }

      }
   }
//cout<<count<<endl;
go(Map,q,row,col,count);



qnode* temp=q.front;
while(1){
    cout<<temp->r<<" "<<temp->c<<endl;
    if(temp==q.rear){
       break;}
    temp=temp->next;

}

for(int i=0;i<row;i++){
    cout<<Map[i]<<endl;
}







    return 0;
}
void go(char m[][1001],Queue &q,int boundr,int boundc,int counter){
qnode* temp=q.rear;
int strow=temp->r;
int stcol=temp->c;

int id=0;
while(1){
        if(m[strow][stcol+1]=='0' && stcol<boundc){//first we always go right
            q.enque(id++,strow,++stcol);
            m[strow][stcol]='2';
        }
        else if (m[strow-1][stcol]=='0' && strow>0){//if we can't go right then we go up
           q.enque(id++,--strow,stcol);
            m[strow][stcol]='2';
        }
        else if(m[strow][stcol-1]=='0' && stcol>0){ //go left then
         q.enque(id++,strow,--stcol);
          m[strow][stcol]='2';
        }
        else if (m[strow+1][stcol]=='0' && strow<boundr){// go down
            q.enque(id++,++strow,stcol);
             m[strow][stcol]='2';
        }
        else{
                 temp=q.rear->prev;
       while(1){
           if(m[temp->r+1][temp->c]=='0' && strow<boundr || m[temp->r-1][temp->c]=='0' && strow<boundr || m[temp->r][temp->c+1]=='0' && stcol<boundc || m[temp->r][temp->c-1]=='0' && stcol>0){
            strow=temp->r;
           stcol=temp->c;
           q.enque(temp->data,strow,stcol);
            break;
           }
           //cout<<temp->r<<" "<<temp->c<<endl;
           strow=temp->r;
           stcol=temp->c;

            q.enque(temp->data,strow,stcol);
            temp=temp->prev;
          }
        }
        if(id==counter){
                //delete(temp);
            return;
        }

}



}
