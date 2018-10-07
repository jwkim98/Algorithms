#include <iostream>

//연습 

using namespace std;

bool** isfriends;

int Count(bool* isOccupied, int size);

int main(){
    int size;
    int inA = 0,inB = 0;

    //get size inputs
    cout<<"num of students"<<endl;
    cin >> size;
    isfriends = new bool*[size];
    for(int i = 0;i < size ; i++){
        isfriends[i] = new bool[size];
    }
    
    bool isOccupied[size];


    //initialize inputs
    for(int i = 0 ; i < size; i++){
        isOccupied[i]=false;
        for(int j = 0 ; j < size; j++){
            isfriends[i][j]=false;
        }  
    }

    //get friend inputs
    cout<<"friends"<<endl;
    while(inA < size && inB < size){
        cin>>inA>>inB;
        if(inA < size && inB < size){
            isfriends[inA][inB]=true;
            isfriends[inB][inA]=true;
        }
        cout<< "int A:"<<inA<< " int B:" <<inB<<endl;
    }
    int ans =Count(isOccupied, size);

    cout<<"total number of possibilities:"<< ans << endl;


    for(int i = 0;  i< size; i ++){
        delete[] isfriends[i];
    }
    delete[] isfriends;


    return 0;
}

int Count(bool* isOccupied, int size){
    static int count = 0;
    int start = 0;

    //find the start index that's not occupied
    for(start = 0 ;start < size; start++){
        if(isOccupied[start]==false){
            isOccupied[start]=true;
            break;
        }
    }


    if(start == size) count++;
    cout<<"start:"<<start<<endl;
    if(start < size){
        for(int index = 0; index < size; index++){
            if(isOccupied[index] == false && isfriends[start][index] == true){
                isOccupied[index] = true;
                Count(isOccupied, size);
                isOccupied[index] = false;
            }
        }
    }

    if(start<size)
        isOccupied[start]=false;

    return count;
}
