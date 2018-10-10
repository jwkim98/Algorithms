#include <iostream>

using namespace std;

int rowSize = 2; 
int colSize;

int *cache;

bool *tileboard[2];

int tiling(int pos);

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

    int ans = tiling(0);
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
