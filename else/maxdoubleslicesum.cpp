



///// second trial

// you can use includes, for example:
// #include <algorithm>
#include <iostream>
#include <vector>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int search(const std::vector<int>& data, int start, int end){
    if(start == end) return 0;
    if(start + 1 == end) return 0;
    
    std::cout<<"start: "<<start <<"end: "<<end<<std::endl;
    
    int middle = (start + end)/2;
    int min_index_left = middle;
    int min_index_right = middle + 1;
    int initial_sum;
    
    int left_sum = data.at(middle);
    int largest_sum_left = -98765;
    for(int index = middle - 1; index >= start; index --){
        if(data.at(index) < data.at(min_index_left))
            min_index_left = index;
        left_sum += data.at(index);
        if(largest_sum_left < left_sum - data.at(min_index_left))
            largest_sum_left = left_sum - data.at(min_index_left);
    }
    
    int right_sum = 0;
    int largest_sum_right = -98765;
    for(int index = middle + 1; index <= end; index++){
        if(data.at(index) < data.at(min_index_right))
            min_index_right = index;
        right_sum += data.at(index);
        if(largest_sum_right < right_sum - data.at(min_index_right))
            largest_sum_right = right_sum - data.at(min_index_right);
    }
    std::cout<<"largest_sum_left: "<<largest_sum_left<<"largest_sum_right: "<<largest_sum_right<<std::endl;
    initial_sum = largest_sum_left + largest_sum_right + std::max(data.at(min_index_left), data.at(min_index_right));
    
    return std::max(initial_sum, std::max(search(data, start, middle - 1), search(data, middle, end)));
}

int solution(std::vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    return search(A, 1, A.size() - 2);
    
}