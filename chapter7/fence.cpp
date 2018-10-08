#include <iostream>

int *rect;
int length;

int largest_rect(int start, int end);
int min(int start, int end);

int main(){
    std::cin>>length;
    rect = new int[length];

    for(int i=0; i<length; i++)
        std::cin>>rect[i];

    int size = largest_rect(0,length-1);
    std::cout<<size;

}

int largest_rect(int start, int end){
    int mid = (start+end)/2;

    if(start >= end){// base case
        return rect[start];
    }

    int leftSize = largest_rect(start, mid);
    int rightSize = largest_rect(mid+1, end);

    int left = mid;
    int right = mid+1;
    int size =0;
    int midSize = 0;
    int index = 2;

    size = min(left,right)*index;
    if(size > midSize)
        midSize = size;

    //returns largest size on two parts unified
    while(left > start || right < end){

        index+=1;
        if(right<end && left==start)
            right+=1;

        if(left>start && right==end)
            left-=1;

        if(left>start && right<end){

            if(rect[left-1]>rect[right+1])
                left-=1;
            else if(rect[left-1]<rect[right+1])
                right+=1;
            else if(rect[left-1] == rect[right+1]){
                left-=1;
                right+=1;
                index+=1;
            }
        }

        size = min(left, right)*index;
        if(size> midSize)
            midSize = size;
    }

    /*
    std::cout<<"left: "<<leftSize<<std::endl;
    std::cout<<"right: "<<rightSize<<std::endl;
    std::cout<<"mid: "<<midSize<<std::endl;
    */

    //return largest among the three
    if(midSize>=leftSize && midSize>=rightSize)
        return midSize;
    if(leftSize>=midSize && leftSize>=rightSize)
        return leftSize;
    if(rightSize>=midSize && rightSize>=leftSize)
        return rightSize;

}

int min(int start, int end){
    int smallest = 10000;
    for(int i= start; i<= end; i++){
        if(rect[i] < smallest)
            smallest = rect[i];
    }

    return smallest;
}
