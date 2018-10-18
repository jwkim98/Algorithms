#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

#define numAlphabets 26

//converts 'a' to 0
inline int toInt(char character){
    return (int)(character - 97);
}

bool findEulerpath(const int index, const std::vector<std::vector<char*>> &graph, std::stack<char*> &order, bool visited[][26]);

void visitAll(const std::vector<std::vector<char*>> &graph, std::stack<char*> &order, bool visited[][26]);


int main(){
    std::vector<char*> column(numAlphabets, NULL);
    std::vector<std::vector<char*>> graph(numAlphabets, column);
    bool visited[numAlphabets][numAlphabets]; // stores visited Edges
    std::stack<char*> order; // stores the return order of findEulerpath

    //Initialize visited to false
    for(int i = 0; i < numAlphabets; i++){
        for(int j = 0; j < numAlphabets; j++){
            visited[i][j] = false;
        }
    }
   
    //receive number of word inputs
    int numWords;
    std::cin>>numWords;

    char* input = new char[11];
    for(int i=0; i<numWords; i++){
        std::cin>>input; // get string input

        char start = toInt(input[0]);
        char end = toInt(input[strlen(input)-1]);
        
        //mark new edge start -> end to graph
        graph[start][end] = new char[11];
        strncpy(graph[start][end], input, strlen(input)); // copy the input to according location
    }

    delete input;

    visitAll(graph, order, visited);

 //   std::cout<<"size of stack: "<<order.size()<<std::endl;

    //if unvisited edge exists, no Euler path exists
    if(numWords == order.size()){
        //print words in stack in reversed order
        while(order.size() > 0){
            char* word = order.top();
            std::cout<<word<<" ";
            delete word;
            order.pop();
        }

    }else{
        std::cout<<"IMPOSSIBLE";
    }
    std::cout<<std::endl;

    //delete all allocated strings in graph
    for(int i = 0; i < graph.size(); i++){
        for(int j = 0; j < graph[i].size(); j++){
            if(graph[i][j] != NULL)
                delete graph[i][j];
        }
    }

    return 0;
}

void visitAll(const std::vector<std::vector<char*>> &graph, std::stack<char*> &order, bool visited[][26]){
    for(int index = 0; index < numAlphabets; index++){
        if(findEulerpath(index, graph, order, visited))
            break; // break if findEulerpath visited some edge
    }
}

//returns true if it visited any edge
bool findEulerpath(const int index, const std::vector<std::vector<char*>> &graph, std::stack<char*> &order, bool visited[][26]){
    //for possible number of Alphabets
    bool hasEdge = false;
    for(int next = 0; next < numAlphabets; next++){
        // if edge from index to next exists, and that edge hasn't been visited
        if(graph[index][next] != NULL && visited[index][next] == false){
            hasEdge = true;
            //findEuler path on next vertex
            visited[index][next] = true;
            findEulerpath(next, graph, order, visited);
            //Add the edge's word to the stack
            char* visitedEdge = new char[11];
            strncpy(visitedEdge, graph[index][next], strlen(graph[index][next]));
            order.push(visitedEdge);
        }
    }
    return hasEdge;
}


