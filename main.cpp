#include <iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

int main()
{
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
   for(int i = 0;i<row;i++){
      eric>>Map[i];
  // cout<<Map[i]<<endl;
   }
   for(int i = 0;i<row;i++){
    for(int j=0;j<col;j++){
            if(j == col-1){
            cout<<Map[i][j]<<endl;
            }
            else{
             cout<<Map[i][j];
            }

    }
   }








    return 0;
}
