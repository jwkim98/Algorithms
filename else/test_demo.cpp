#include <vector>

// you can use includes, for example:
// #include <algorithm>
#include <iostream>
#include <string>
#include <deque>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;
const std::vector<std::string> type = {"OK",
"Wrong answer",
"Time limit exceeded",
"Runtime error"
};

std::string first_number_string(const std::string& str){
    int start_index = 0;
    for(int index = 0; index < str.size(); index ++){
        if(str.at(index) >= 48 || str.at(index) <= 57){ // if integer
            start_index = index;
        }
    }
    return str.substr(start_index - 1);
}

int solution(std::vector<string> &T, std::vector<string> &R) {
    // write your code in C++14 (g++ 6.2.0)
    std::deque<int> score_list(T.size() + 1, 0);
    
    for(int index = 0; index < T.size(); index ++){
        const std::string& test_str = T.at(index);
        std::string num_index_str = first_number_string(test_str);
        std::cout<<num_index_str<<std::endl;
        int test_case_num = std::stoi(num_index_str);
        
        if(type.at(0).compare(R.at(test_case_num)) == 0){
            if(score_list.at(test_case_num) != -1)
                score_list.at(test_case_num) = 1;
        }else{
            score_list.at(test_case_num) = -1; //wrong
        }
    }
    
    int score_sum = 0;
    int num_of_test_cases = 0;
    for(int index = 1; index < score_list.size(); index++){
        if(score_list.at(index) != 0)
            num_of_test_cases ++;
        if(score_list.at(index) == 1)
            score_sum += 100;
    }
    return score_sum/num_of_test_cases;
}