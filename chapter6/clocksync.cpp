#include <iostream>
#include <vector>
#include <array>
#include <iterator>

using namespace std;

int minimumPress(int depth = 0);
bool checkClocks(int* pressedArray);

array<vector<int>,10> mappings{
    vector<int>{0,1,2},
    vector<int>{3,7,9,11},
    vector<int>{4,10,14,15},
    vector<int>{0,4,5,6,7},
    vector<int>{6,7,8,10,12},
    vector<int>{0,2,14,15},
    vector<int>{3,14,15},
    vector<int>{4,5,7,14,15},
    vector<int>{1,2,3,4,5},
    vector<int>{3,4,5,9,13}
};

int clocks[16];

int main(){

    cout<<"input clocks"<<endl;
    for(int i=0; i<16; i++){
        int input;
        cin>>input;
        clocks[i] = input/3;
    }

    int answer = minimumPress();

    cout<<"minimum presses: " << answer<< endl;

}



int minimumPress(int depth){
    static int numPressed[10];
    static int minPressCount = 3*10; // can't be larger than 3*10
    if(depth==0){
        for(int i=0; i<10; i++){
            numPressed[i] = 0;
        }
    }

    if(depth < 10)
    for(int i=0; i<4; i++){
        numPressed[depth] = i;
        minimumPress(depth+1);
    }

    if(depth == 10){
        int pressCount=0;
        for(int i=0; i<10; i++)
            pressCount += numPressed[i];
        if(checkClocks(numPressed)){
            if(pressCount<minPressCount)
                minPressCount=pressCount;
        }
    }

    return (minPressCount==3*10) ? -1 : minPressCount;
}

bool checkClocks(int* pressedArray){
    bool matched = true;
    int newClocks[16];
    vector<int>::iterator ptr;

    for(int i=0; i<16; i++){
        newClocks[i] = clocks[i];
    }

    for(int i=0; i<10; i++){
        for(ptr = mappings[i].begin(); ptr<mappings[i].end(); ptr++)
            newClocks[*ptr] += pressedArray[i]; 
    }
    for(int i=0; i<16; i++){
//        cout<<" "<< newClocks[i];
        if(newClocks[i]%4!=0){
            matched=false;
            break;
        }
    }
//    cout<<"\n";
    return matched;
}
