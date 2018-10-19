#include <iostream>
#include <deque>
#include <vector>

#define INF  98765

int DivisionPoint(const int index, const bool isRoot, const std::vector<std::vector<bool>> &adj, std::vector<int> &visitOrder, std::vector<bool> &isDivisionPoint);


void visitAll(const std::vector<std::vector<bool>> &adj, std::vector<bool> &isDivisionPoint);

int main(){

    int graphSize;
    std::cin>>graphSize;
    std::vector<bool> column(graphSize, false);
    std::vector<std::vector<bool>> adj(graphSize, column);

    std::vector<bool> isDivisionPoint(graphSize, false);

    for(int i = 0; i < graphSize; i++){
        std::cout<<"graph"<<i<<" is connected to: ";
        int input;
        std::cin>>input;

        while(input < graphSize && input >= 0){
            adj[i][input] = true;
            adj[input][i] = true;
            std::cin>>input;
        }
    }

    for(int i =0; i <graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            std::cout<<adj[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    visitAll(adj, isDivisionPoint);

    for(int index = 0; index < isDivisionPoint.size(); index++){
        if(isDivisionPoint[index] == true)
            std::cout<<index<<" ";
    }
}

void visitAll(const std::vector<std::vector<bool>> &adj, std::vector<bool> &isDivisionPoint){
    std::vector<int> visitOrder(adj.size(), INF);
    for(int index = 0; index < adj.size(); index++){
        if(visitOrder[index] == INF)
            DivisionPoint(index, true, adj, visitOrder, isDivisionPoint);
    }
}


//returns minimum visitedOrder vertex number
int DivisionPoint(const int index, const bool isRoot, const std::vector<std::vector<bool>> &adj, std::vector<int> &visitOrder, std::vector<bool> &isDivisionPoint){
    static int visitNum = 0;

    visitOrder[index] = visitNum++;
    std::cout<<"visitid: "<<index<<" with ordering: "<<visitOrder[index]<<std::endl;

    int minPoint = INF; //minimum visitOrder point of this vertex
    int childMin = INF;
    int childrenNum = 0;

    for(int next = 0; next < adj[index].size(); next++){

        if(adj[index][next]){
            childrenNum++;
            std::cout<<"next: "<<next<<" visitOrder: "<<visitOrder[next]<<std::endl;
            if(visitOrder[next] < minPoint){
                minPoint = visitOrder[next];
            }
        }

        if(adj[index][next]  && visitOrder[next] == INF){
            //if this vertex's children has connection to it's ancestors, this isn't division point
            int min = DivisionPoint(next, false, adj, visitOrder, isDivisionPoint);
            if(childMin < min){
                childMin = min;
            }
            if(min >= visitOrder[index])
                isDivisionPoint[index] = true;
            std::cout<<"child min: "<<min<<std::endl;
        }
    }

    std::cout<<"minVisitOrder: "<<minPoint<<std::endl;

    if(isRoot) isDivisionPoint[index] = (childrenNum > 1);

    return (childMin < minPoint) ? childMin : minPoint;
}
