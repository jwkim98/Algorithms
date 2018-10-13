#include <iostream>
#include <vector>
#include <cmath>

class node{
    public:
        int depth;
        std::vector<node*> *children;
        node(int depth){
            this->depth = depth;
            children = new nodes<node*>;
        }
        ~node(){
            delete nodes;
        }
};

class fortress{
    public:
        int x,y;
        int r;
        int num;
        std::vector<int> *contained;
        node(int x, int y, int r, int num){
            this->x = x;
            this->y = y;
            this->r = r;
            this->num = num;
            contained = new std::vector<int>
        }
        ~node(){
            delete contained;
        }
};

int main(){
    std::vector<fortress> *fortresses = new std::vector<fortress>;
    int numFortresses;
    std::cin>>numFortresses;
    
    fortresses.reserve(numFortresses);

    for(int i=0; i<numFortresses; i++){
        int x,y,r;
        std::cin>>input>>x>>y;
        fortresses->push_back(new fortress(x,y,r,i));

    }
}

node* create_tree(std::vector<fortress> *fortresses){
    node* root = new node(0);

    int current = 0;
    for(int depth=1; depth<fortresses->size(); depth++){
        if((*fortresses)[i].contained->size() == i){
            if(contains(current, &(*fortresses)[i]))
                root->children->push_back(
        }
    }
}

void analyze_fortresses(std::vector<fortress> *fortresses){
    for(int i=0; i<fortresses->size(); i++){
        for(int j=0; i<fortresses->size(); i++){
            if(i!=j){
               float pointDistance = distance(&(*fortresses)[i], &(*fortresses)[j]);
               if((float)(*fortresses)[j].r > pointDistance + (float)(*fortresses)[i].r)
                   (*fortresses)[i].contained->push_back((*fortresses)[j].num);
            }
        }
    }
}

float distance(const fortress *first, const fortress *second){
    return sqrt(pow((float)(first->x - second->x),2) + pow((float)(first->y - second->y),2));
}

bool contains(int num, const fortress *fort){
    for(int i=0; i<(*fort).contained->size()){
        if((*(*fort).contained)[i] == num)
            return true;
    }
    return false;
}
