#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#define INF 98765

inline int toInt(char input){
    return (int)input - 0x30;
}


int findAll(const int graphSize, std::vector<std::vector<int>> &adj, std::vector<int> &visitOrder);

int findCycle(const int index, std::vector<std::vector<int>> &adj, std::vector<int> &visitOrder, std::deque<int> &executing);

int main(){

    int graphSize;
    std::cin>>graphSize;
    std::vector<int> column(graphSize, -1);
    //-1: not connected 0: unvisited, 1:tree edge, 2: forward edge, 3: back edge, 4: cross edge
    std::vector<std::vector<int>> adj(graphSize, column);
    std::vector<int> visitOrder(graphSize, INF);
    for(int i = 0; i < graphSize; i++){
        std::cout<<"graph "<<i<<" is connected to: ";

        char input;
        std::cin>>input;
        while(toInt(input) < graphSize && toInt(input) >= 0){
//            std::cout<<"a"<<std::endl;
            adj[i][toInt(input)] = 0; // connect to vertices (marks edge between two vertices)
            std::cin>>input;
        }
    }

    //prints adjacency matrix
    for(int i = 0; i<graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            std::cout<<adj[i][j]<<" ";
        }
        std::cout<<std::endl;
    }


    int numCycles = findAll(graphSize, adj, visitOrder);

    //prints adjacency matrix
    for(int i = 0; i<graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            std::cout<<adj[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<"number of cycles: "<<numCycles<<std::endl;

    return 0;
}

int findAll(const int graphSize, std::vector<std::vector<int>> &adj, std::vector<int> &visitOrder){
    std::deque<int> executing;
    int numCycle = 0;
    for(int index = 0; index < graphSize; index++){
        if(visitOrder[index] == INF){
            numCycle = findCycle(index, adj, visitOrder, executing);
        }
    }

    return numCycle;
}



int findCycle(const int index, std::vector<std::vector<int>> &adj, std::vector<int> &visitOrder, std::deque<int> &executing){

    static int visitNum = 0;
    static int numCycle = 0;

    visitOrder[index] = visitNum++;

    std::cout<<"visited "<<index<<std::endl;
    
    executing.push_back(index);

    for(int next = 0; next < adj[index].size(); next++){

        if(adj[index][next] != 0)
            continue;

        //if index has been visited earlier, this edge must be back edge or cross edge
        if(visitOrder[next] < visitOrder[index]){
            std::deque<int>::iterator itr;
            //if index is in parent stack this must be back edge -> cycle
            itr = std::find(executing.begin(), executing.end(), next);
            if(itr != executing.end()){
                std::cout<<"itr: "<<*itr<<std::endl;
                adj[index][next] = 3;
                numCycle++; //increment numCycle
            }else{ // if index is not in parent stack, this must be cross edge
                adj[index][next] = 4;
            }
        }

        //forward edge if next is found later, and has been visited
        if(visitOrder[next] > visitOrder[index] && visitOrder[next] != INF){
            adj[index][next] = 2;
        }

        //if it this vertex has connected edge, and didn't visit there yet, visit it
        if(adj[index][next] == 0){
            adj[index][next] = 1;//this edge should be tree edge
            findCycle(next, adj, visitOrder, executing);
        }
    }

    executing.pop_back();
    return numCycle;
}


