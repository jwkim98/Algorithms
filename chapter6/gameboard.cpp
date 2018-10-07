#include<iostream>
#include<vector>
#include<stdio.h>

using namespace std;


class gameBoard
{
    public:
        bool **board;
        int height;
        int width;
        gameBoard(int height, int width):height(height), width(width)
        {
            board = new bool*[height+1];
            for(int i=0; i<height+1; i++)
                board[i]=new bool[width+1];

            for(int i=0; i<height+1; i++)
                for(int j=9; j<width+1; j++)
                    board[i][j]=false;
            
        }

        ~gameBoard()
        {
            for(int i=0; i<height+1; i++){
                delete[] board[i];
            }
            delete[] board;
        }
};

int fill(gameBoard* board, int height, int width, int depth);

bool **baseBoard;//false:black, true:white
int numWhite;

int main(){
    int width, height;

    cout<<"width:"<<endl;
    cin>>width;
    cout<<"height:"<<endl;
    cin>>height;

    baseBoard = new bool*[height+1];
    for(int i=0; i<height+1; i++)
        baseBoard[i]=new bool[width+1];

    for(int i=0; i<height+1; i++)
        for(int j=9; j<width+1; j++)
            baseBoard[i][j]=false; // initialize base with false



    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            char input;
            cin>>input;
            if(input=='.')
            {
                baseBoard[i][j]=true;
                numWhite++;
            }
        }
        cout<<"\n";
    }

   //print base
    cout<<"base:"<<endl;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++){
            if(baseBoard[i][j]==true)
                cout<<".";
            else
                cout<<"3";
        }
        cout<<"\n";
    }

    cout<<"hello"<<endl;
    int answer;
    if(numWhite%3 !=0) 
        answer=0;
    else
    {
        int divideBy=1;
        for(int i=1; i<=numWhite/3; i++)
            divideBy*=i;
        answer = fill(NULL,height,width,0);
        cout<<"before divide:" <<answer<<endl;
        answer= answer/divideBy;

    }

    cout<<"answer: "<< answer <<endl;

    for(int i=0; i<height +1; i++){
        delete[] baseBoard[i];
    }
    delete[] baseBoard;
}


int fill(gameBoard* board, int height, int width, int depth){
    static int count=0;
    bool isLast=true;
    bool isFirst=false;
    if(board == NULL)
    {
        board = new gameBoard(height,width);
        isFirst=true;
    }
  //  cout<<"count: "<<count<<endl;
    //* *
    //* 

    int startX=-1,startY=-1;

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(baseBoard[i][j]==true && board->board[i][j]==false){
                startX=i;
                startY=j;
                break;
            }
            if(startX!=-1)
                break;
        }
    }
    if(startX!=-1 && startY!=-1){

        if(baseBoard[startX][startY]==true && baseBoard[startX+1][startY]==true && baseBoard[startX][startY+1]==true)
            if(board->board[startX][startY]==false && board->board[startX+1][startY]==false && board->board[startX][startY+1]==false){

                board->board[startX][startY]=true;
                board->board[startX+1][startY]=true;
                board->board[startX][startY+1]=true;

                fill(board, height, width,depth+1);

                board->board[startX][startY]=false;
                board->board[startX+1][startY]=false;
                board->board[startX][startY+1]=false;

                isLast=false;
            }

        if(baseBoard[startX][startY]==true && baseBoard[startX+1][startY]==true && baseBoard[startX+1][startY+1]==true)
            if(board->board[startX][startY]==false && board->board[startX+1][startY]==false && board->board[startX+1][startY+1]==false){

                board->board[startX][startY]=true;
                board->board[startX+1][startY]=true;
                board->board[startX+1][startY+1]=true;

                fill(board, height, width,depth+1);

                board->board[startX][startY]=false;
                board->board[startX+1][startY]=false;
                board->board[startX+1][startY+1]=false;

                isLast=false;
            }

        if(baseBoard[startX][startY]==true && baseBoard[startX+1][startY+1]==true && baseBoard[startX][startY+1]==true)
            if(board->board[startX][startY]==false && board->board[startX+1][startY+1]==false && board->board[startX][startY+1]==false){

                board->board[startX][startY]=true;
                board->board[startX+1][startY+1]=true;
                board->board[startX][startY+1]=true;

                fill(board, height, width,depth+1);

                board->board[startX][startY]=false;
                board->board[startX+1][startY+1]=false;
                board->board[startX][startY+1]=false;

                isLast=false;
            }

        if(startY>0)
            if(baseBoard[startX][startY]==true && baseBoard[startX+1][startY]==true && baseBoard[startX+1][startY-1]==true)
                if(board->board[startX][startY]==false && board->board[startX+1][startY]==false && board->board[startX+1][startY-1]==false){

                    board->board[startX][startY]=true;
                    board->board[startX+1][startY]=true;
                    board->board[startX+1][startY-1]=true;

                    fill(board, height, width,depth+1);

                    board->board[startX][startY]=false;
                    board->board[startX+1][startY]=false;
                    board->board[startX+1][startY-1]=false;

                    isLast=false;
                }

    }
    bool equivalent=true;
    if(isLast=true && depth*3== numWhite){
        cout<<"\ngraph"<<endl;
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++){
                if(board->board[i][j]==true)
                    printf(". ");
                else
                    printf("# ");
                if(board->board[i][j] != baseBoard[i][j])
                {
                    equivalent = false;
                    
                }
            }
            printf("\n");
        }
    }

    if(equivalent == true && isLast == true)
        count++;


    if(isFirst==true)
        delete board;

    return count;
}
