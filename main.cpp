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
qnode* parent; //for BFS backtracking
qnode(int d,int rr,int cc){
data = d;
r=rr;
c=cc;
next=NULL;
prev=NULL;
parent=NULL;

}
};


struct Queue{
qnode *front, *rear,*prev;
Queue(){
front = rear = NULL;
}


void enque(int x,int r,int c){
//create a new node
qnode *T = new qnode(x,r,c);
//if queue is empty then new node is front and rear both
if(rear==NULL){
    front=rear=T;
    return;
}

// add the new node at the end of the queue
//let the previous of temp be the previous of rear
T->prev=rear;
rear->next=T;
rear=T;

}

void enque(int x,int r,int c,qnode *father){
//create a new node
qnode *t = new qnode(x,r,c);
//point parent to father
t->parent=father;
//if queue is empty then new node is front and rear both
if(rear==NULL){
    front=rear=t;
     return;
}



// add the new node at the end of the queue
//let the previous of temp be the previous of rear
t->prev=rear;
rear->next=t;
rear=t;

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
if(rear==NULL)
    return;
//let rear point to the previous of rear
qnode* temp=rear;
rear=rear->prev;
rear->next=NULL;
if(rear=NULL){
    front=NULL;
}
delete(temp);

}

bool emptyque(){
if(front==NULL && rear==NULL){
    return true;
}
else{
    return false;
}
}
};

void go(char m[][1001],Queue &q,int boundr,int boundc,int counter);

void BFS(char m[][1001],Queue &q, int boundr,int boundc,char target);

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
  qnode* iter=q.front;
//cout<<count<<endl;
go(Map,q,row,col,batlife);
BFS(Map,q,row,col,'R');

for(int i=0;i<row;i++)
    cout<<Map[i]<<endl;

//iter=q.front;
while(1){
   cout<<iter->r<<" "<<iter->c<<endl;
   iter=iter->next;
   if(iter==NULL){
    break;
   }

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
temp=NULL;
}



void BFS(char m[][1001],Queue &q, int boundr,int boundc,char target){


//create a queue for row
//Queue rq;
//create a queue for column
//Queue cq;
Queue store;
int row=q.rear->r;
int col=q.rear->c;
store.enque(0,row,col);



bool visited[boundr][boundc];
    for(int i =0;i<boundr;i++){
    for(int j=0;j<boundc;j++){
    if(m[i][j]=='1'){
    visited[i][j]=true;
    }
    else{
        visited[i][j]=false;
    }

    }
}


//apply DFS on the starting cell , which is the rear of the q
//every time we go right first and then go up and then go left then go right
qnode *traverse=store.front;//point temp to the path front
int dis=0;// count the distance
bool finish=false;// check if the destination is reached
while(1){
          //cout<<q.rear->r<<" "<<q.rear->c<<endl;
int move[4][2]={{0,1},{1,0},{0,-1},{-1,0}};   //move up down left right
//qnode* Next;
bool finish=false;
for(int i=0;i<4;i++){

        row=traverse->r+move[i][0];
        col=traverse->c+move[i][1];


        if(row>boundr || row<0 || col>boundc || col<0){
            //out of bound
            continue; //skip the rest of the for loop
        }

        if(visited[row][col]==false){// unvisited cell
                visited[row][col]=true;
            store.enque(dis,row,col,traverse);



        }
        if(m[row][col]==target){

          finish=true;
          break;
        }
}
//update the traverse pointer
traverse=traverse->next;

if(finish==true){
traverse=NULL;
    break;
}

dis++; //increase the distance after every iteration
}

// if we come to here means that we finish searching
//need to start combining the queue
qnode* J=store.rear;
Queue arr;
while(1){
        row=J->r;col=J->c;
    arr.enque(0,row,col);
     if(row==store.front->r && col==store.front->c ){
        break;
    }
    J=J->parent;
}
J=arr.rear;
while(1){
 if(J->next==NULL){
    J=J->prev;
  continue;
}
     row=J->r;col=J->c;
  q.enque(0,row,col);
  if(J->prev==NULL){
    break;
  }
 J=J->prev;
}
return;
}




