#include <iostream>
#include <queue>
#include <deque>


int main(){
    std::priority_queue<int> maxHeap;

    std::deque<int> container;

    int inputNum = 0;
    std::cin>>inputNum;
    for(int i=0; i<inputNum; i++){
        int input;
        std::cin>>input;
        maxHeap.push(input);
    }

    while(maxHeap.size() > 0){
        std::cout<<maxHeap.top()<<" ";
        maxHeap.pop();
    }
    
}
