#include<iostream>
#include<vector>
#include<algorithm>
#include<type_traits>

int main(){
    std::vector<int> vect = {1,2,3,4,5};
    auto it = std::find(std::begin(vect), std::end(vect), 3);
    auto is_reference = std::is_reference<int&&>();
    //it = vect.end();
    //it+=1;
    std::cout<<"*it :"<<*it <<std::endl;
    std::cout<<is_reference<<std::endl;

    return 0;
}