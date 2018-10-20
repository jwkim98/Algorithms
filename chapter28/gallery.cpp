#include <iostream>
#include <vector>

int visitAll(std::vector<std::vector<bool>> &adj);

int numCamera(const int index, bool set, std::vector<std::vector<bool>> &adj, std::vector<bool> &visited);

int main(){
    int graphSize, edgeNum;
    std::cin>>graphSize>>edgeNum;
    std::vector<bool> col(graphSize, false);
    std::vector<std::vector<bool>> adj(graphSize, col);

    for(int i = 0; i < edgeNum; i++){
        int con1, con2;
        std::cin>>con1>>con2;

        if(con1 < graphSize and con2 < graphSize){
            adj[con1][con2] = true;
            adj[con2][con1] = true;
        }
    }

    std::cout<<"min number of required camera:"<<visitAll(adj);
}

int visitAll(std::vector<std::vector<bool>> &adj){
    int sum = 0;
    std::vector<bool> visited(adj.size(), false);

    for(int index = 0; index < adj.size(); index++){
        sum += std::max(numCamera(index, false, adj, visited), numCamera(index, true, adj, visited));
    }

    return sum;
}


int numCamera(const int index, bool set, std::vector<std::vector<bool>> &adj, std::vector<bool> &visited){

    if(visited[index])
        return 0;

    visited[index] = true;

    int num = 0;
    for(int next = 0; next < adj[index].size(); next++){
        if(adj[index][next] && visited[next] == false){
            num += numCamera(next, !set, adj, visited);
        }
    }

    if(set) num++;

    return num;
}


