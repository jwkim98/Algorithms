#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

void dfsAll(const std::vector<bool*> &matrix, std::stack<char> &sorted, std::vector<bool>&visited);

void dfs(const int index, const std::vector<bool*> &matrix, std::stack<char> &sorted, std::vector<bool> &visited);


int main(){
    int inputNum;
    const int numAlphabets = 26;
    std::cin>>inputNum;
    std::vector<bool*> matrix; 
    std::stack<char> sorted;
    std::vector<bool> visited;

    matrix.reserve(numAlphabets);
    visited.reserve(numAlphabets);

    //Construct adjacency matrix
    for(int i=0; i<numAlphabets; i++){
        matrix.push_back(new bool[numAlphabets]);
        for(int j=0; j<numAlphabets; j++){
            matrix[i][j] = false;
        }
        visited.push_back(true); //visit only declared alphabets
    }

    char* previous = new char[20];
    char* str = new char[20];
    bool invalid = false;

    for(int i=0; i<inputNum; i++){
        std::cin>>str;

        if(i != 0){
            int idx = 0;
            while(previous[idx] == str[idx] && idx < strlen(previous)  && idx < strlen(str) ){
                idx++;
            }

            if(idx < strlen(previous)  && idx < strlen(str) ){ 
                if(matrix[str[idx] - 97][previous[idx] - 97] == true)
                    invalid = true;
                matrix[previous[idx] - 97][str[idx] - 97] = true;
                visited[previous[idx] - 97] = false;
                visited[str[idx] - 97] = false;
            }
        }

        strncpy(previous, str, sizeof(str) + 1);
    }

    std::cout<<std::endl;

//checking the adjacency matrix

/*
    for(int i=0; i<numAlphabets; i++){
        for(int j=0; j<numAlphabets; j++){
            std::cout<<matrix[i][j];
        }
        std::cout<<std::endl;
    }
*/


    if(invalid == true){
        std::cout<<"INVALID HYPOTHESIS"<<std::endl;
    }
    else{
        dfsAll(matrix, sorted, visited);

        while(!sorted.empty()){
            std::cout<<sorted.top()<<" ";
            sorted.pop();
        }
    }

    delete previous;
    delete str;

}

void dfsAll(const std::vector<bool*> &matrix, std::stack<char> &sorted, std::vector<bool>&visited){
    for(int i=0; i<visited.size(); i++){
        if(visited[i] == false){
            dfs(i, matrix, sorted, visited);
        }
    }
}

void dfs(const int index, const std::vector<bool*> &matrix, std::stack<char> &sorted, std::vector<bool> &visited){

    if(visited[index] == true)//return right away if node is already visited
        return;

    //visit all connected nodes
    for(int i=0; i<matrix.size(); i++){//size of columns should be same as size of rows
        if(matrix[index][i] == true){
            dfs(i, matrix, sorted, visited);
        }
    }

    visited[index] = true;
    sorted.push((char)(index + 97)); // push into sorted in the order dfs returned
    return;
}

