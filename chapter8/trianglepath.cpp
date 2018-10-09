#include <iostream>

using namespace std;

int cache[50][50];
int path[50][50];
int size;

int maxpath(int row,int col);

int main(){

    for(int i=0;i<50;i++)
        for(int j=0; j<50 ; j++){
            cache[i][j]=-1;
            path[i][j]=0;
        }
    cin>>size;
    for(int i=0; i<size; i++){
        for(int j=0; j <=i; j++)
            cin>>path[i][j];
        cout<<"\n";
    }
    int ans =maxpath(0,0);
    cout<<ans<<endl;
    return 0;
}

int maxpath(int row, int col){

    if(cache[row][col]>-1)
        return cache[row][col];

    if(row == size-1) //base case;
        return path[row][col];

    if(row<size-1){
        int down = maxpath(row+1,col);
        int rightdown = maxpath(row+1,col+1);
//        cout<<"down: "<<down<<endl;
//        cout<<"rightdown: "<<rightdown<<endl;
        cache[row][col] = path[row][col] + ((down>rightdown)? down:rightdown);
//        cout<<"returns: "<<cache[row][col]<<endl;

        return cache[row][col];
    }
}


