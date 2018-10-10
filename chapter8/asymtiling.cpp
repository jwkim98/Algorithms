#include <iostream>
using namespace std;

int **board; //0: empty , 1: occupied
struct Tile{
    int horizontal[2] = {0,1};
    int vertical[2] = {0,1};
}tile;

int asymtiling(bool first);
void resetBoard();

int rowSize=2;
int colSize;
int ans;

int main(){
    
    cin>>colSize;
    board = new int*[rowSize];
    for(int i=0; i<rowSize; i++){
        board[i] = new int[colSize];
    }

    resetBoard();

    int allcase = asymtiling(true);
    cout<<"allcase: "<<allcase<<endl;
    
    if(colSize%2 == 0){
        colSize = colSize/2;
        resetBoard();
        int symcase = asymtiling(true);
        colSize -= 1;
        resetBoard();
        symcase += asymtiling(true);

        ans= allcase - symcase;
        if(ans<0)
            ans = 1000000007 + ans;
        else
            ans = ans%1000000007;
    }else if(rowSize%2==0){
        colSize = (colSize-1)/2;
        resetBoard();
        int symcase = asymtiling(true);

        ans = allcase - symcase;
        if(ans<0)
            ans = 1000000007 + ans;
        else
            ans = ans%1000000007;
    }

    cout<<ans<<endl;

    cout<<"rowSize:"<<rowSize<< "colSize: "<<colSize<<endl;

    for(int i=0; i<rowSize; i++)
        delete[] board[i];
    delete[] board;
    
    return 0;

}

int asymtiling(bool first){
    int startRow = -1;
    int startCol = -1;
    static int count=0;
    if(first)
        count = 0;

    for(int i=0; i<rowSize; i++){
        for(int j=0; j<colSize; j++){
            if(board[i][j] == 0){
                startRow = i;
                startCol = j;
                break;
            }
        }
        if(startRow != -1 && startCol != -1)
            break;
    }

    if(startRow == -1 && startCol == -1){
        count++;
        if(count > 1000000007)
            count = count%1000000007;
        return count;
    }

    board[startRow][startCol]=1;

//    cout<<"row:"<<startRow<<" col: "<<startCol<<endl;

    if(startCol+tile.horizontal[1]<colSize && board[startRow][startCol + tile.horizontal[1]] == 0){
        board[startRow][startCol + tile.horizontal[1]] = 1;
        asymtiling(false);
        board[startRow][startCol + tile.horizontal[1]] = 0;
    }
    if(startRow+tile.vertical[1]<rowSize && board[startRow + tile.vertical[1]][startCol] == 0){
        board[startRow+tile.vertical[1]][startCol] = 1;
        asymtiling(false);
        board[startRow+tile.vertical[1]][startCol] = 0;
    }

    board[startRow][startCol]=0;
    return count;
}

void resetBoard(){
    for(int i=0; i<rowSize; i++)
        for(int j=0; j<colSize; j++)
            board[i][j] = 0;
}
