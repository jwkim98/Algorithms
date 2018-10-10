/*
    newAsymtiling.cpp
*/

#include <iostream>

using namespace std;

int rowSize = 2; 
int colSize;

int *cache;

bool *tileboard[2];
void resetResources();

int tiling(int pos = 0);

int main(){

    cin>>colSize;
    for(int i=0; i<rowSize; i++){
        tileboard[i] = new bool[colSize];
        for(int j=0; j<colSize; j++)
            tileboard[i][j] = false;
    }

    cache = new int[colSize];

    for(int i=0; i<colSize; i++)
        cache[i] = -1;

    int everycase = tiling();

    resetResources(); // reset cache and tileboard

    int symcase = 0;
    if(colSize%2 == 0 && colSize != 0){ // even number
        colSize /= 2;
        symcase = tiling();
        colSize -= 1;
        symcase += tiling();
    }else if(colSize != 0){
        colSize = (colSize-1)/2;
        symcase = tiling();
    }

    int ans = everycase - symcase;// exclude symmetric cases
    ans = (ans>=0) ? ans : (1000000007 - ans);

    cout<<ans<<endl;

    for(int i=0; i<rowSize; i++)
        delete[] tileboard[i];

    return 0;
}

int tiling(int pos){
    
    if(pos==colSize) // base cases
        return 1;
    if(pos+1 == colSize) // only one space left
        return 1;
    if(cache[pos] > 0) // if the case has been analyzed before
        return cache[pos];

    for(int i=0; i<rowSize; i++)
        tileboard[i][pos] = true;

    int caseA = tiling(pos+1);
    for(int i=0; i<rowSize; i++)
        tileboard[i][pos] = false;

    for(int i=0;i<rowSize;i++){
        tileboard[i][pos] = true;
        tileboard[i][pos+1] = true;
    }

    int caseB = tiling(pos+2);

    for(int i=0;i<rowSize;i++){
        tileboard[i][pos] = false;
        tileboard[i][pos+1] = false;
    }
    
    cache[pos] = (caseA + caseB)%1000000007;

    return cache[pos];

}

void resetResources(){
    for(int i=0; i<rowSize; i++)
        for(int j=0; j<colSize; j++){
            tileboard[i][j] = false;
        }
    for(int i=0; i<colSize; i++)
        cache[i] = -1;
}
