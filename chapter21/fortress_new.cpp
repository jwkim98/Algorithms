#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


class Node{
    public:
        int num;
        Node *parent;
        std::vector<Node*>  children;
        Node(int num, Node* parent){
            this->num = num;
            this->parent = parent;
        }
        ~Node(){
            std::vector<Node*>::iterator itr;
            for(itr = children.begin(); itr != children.end(); itr++)
                delete *itr;
        }
};

class fortress{
    private: 
        std::vector<int> ContainedBy;
    public:
        int x,y,radius;
        int num;
        fortress(int x,int y,int radius, int num){
            this->x = x;
            this->y = y;
            this->radius = radius;
            this->num = num;
        }

        //get distance between this and other, and put it to isContainedBy if this fortress is contained by the other
        float distanceBeetween(const fortress* other){
            float distance = sqrt(pow((float)x - (float)other->x,2.0) + pow((float)y - (float)other->y,2.0));
            if((float)other->radius > (distance + float(radius))){
                if(!this->isContainedBy(other->num)) // don't add of it's already included
                    ContainedBy.push_back(other->num);
            }
            return distance;
        }

        //returns if this fortress is contained by parameterized fortress
        bool isContainedBy(int other){
            std::vector<int>::iterator itr;
            itr = std::find(ContainedBy.begin(), ContainedBy.end(), other);
            if(itr != ContainedBy.end())
                return true;
            else
                return false;
        }

        //depth is same as number of fortresses surrounding this fortress
        int depth(){
            return ContainedBy.size();
        }
};


void constructTree(std::vector<fortress*> *fortresses, Node* currentNode, int currentDepth);

int findLongestPath(Node* currentNode);

int getHeight(Node* node);

int main(){
    std::vector<fortress*> fortresses;
    int numFortresses;
    std::cin>>numFortresses;

    fortresses.reserve(numFortresses);
    for(int num=0; num<numFortresses; num++){
        int x,y,radius;
        std::cin>>x>>y>>radius;
        fortresses.push_back(new fortress(x,y,radius,num));
    }

    std::vector<fortress*>::iterator currentItr;
    std::vector<fortress*>::iterator checkItr;
    for(currentItr = fortresses.begin(); currentItr != fortresses.end(); currentItr++){
        for(checkItr = fortresses.begin(); checkItr != fortresses.end(); checkItr++){
    //        std::cout<<"checkNum: "<<(*checkItr)->num<<std::endl;
            (*currentItr)->distanceBeetween(*checkItr);
        }
    }

//    std::cout<<"before constructTree "<<std::endl;

    currentItr = fortresses.begin();
    Node* root = new Node((*currentItr)->num,NULL);
    constructTree(&fortresses, root, 0);
    int ans = findLongestPath(root);
    std::cout<<"Longest path: "<<ans<<std::endl;
    delete root;
    for(currentItr = fortresses.begin(); currentItr != fortresses.end(); currentItr++){
        delete *currentItr;
    }

}

void constructTree(std::vector<fortress*> *fortresses, Node* currentNode, int currentDepth){
    
    std::vector<fortress*>::iterator checkItr;
//    std::cout<<"\ncurrentNode: "<<currentNode->num<<std::endl;

    //if checked fortress is contained by current fortress, and if depth is 1 lower than current fortress, add new node with checkfortress's number
    for(checkItr = fortresses->begin(); checkItr != fortresses->end(); checkItr++){
        if((*checkItr)->depth() == currentDepth + 1 && (*checkItr)->isContainedBy(currentNode->num)){
            currentNode->children.push_back(new Node((*checkItr)->num,currentNode));
        //    std::cout<<(*checkItr)->num;
        }
    }

    //iterate through child nodes, and construct tree on them 
    std::vector<Node*>::iterator childrenItr;
    for(childrenItr = currentNode->children.begin(); childrenItr != currentNode->children.end(); childrenItr++){
        constructTree(fortresses, *childrenItr, currentDepth+1);
    }
}

int findLongestPath(Node* currentNode){
    std::vector<int> pathLength;
    std::vector<int> heights;
    std::vector<Node*>::iterator childrenItr;
    for(childrenItr = currentNode->children.begin(); childrenItr != currentNode->children.end(); childrenItr++){
        pathLength.push_back(findLongestPath(*childrenItr));
        heights.push_back(getHeight(*childrenItr));
    }

//    std::cout<<"node: "<<currentNode->num<<std::endl;

    if(pathLength.size() == 0)
        return 0;
    else{
        std::vector<int>::iterator itr;
        std::vector<int>::iterator firstposition;
        int first = -1, second = -1;
        for(itr = heights.begin(); itr != heights.end(); itr++){
            if(first<*itr){
                first = *itr;
                firstposition = itr;
            }
        }

        for(itr = heights.begin(); itr != heights.end(); itr++){
            if(second < *itr && itr != firstposition)
                second = *itr;
        }

        int thisNodePath = first+second+2;

        int longestchildPath = 0;
        for(itr = pathLength.begin(); itr != pathLength.end(); itr++){
            if(longestchildPath < *itr)
                longestchildPath = *itr;
        }

        return (thisNodePath > longestchildPath) ? thisNodePath : longestchildPath;
    }
}

int getHeight(Node* node){
//    std::cout<<"height"<<node->num<<node->children.size()<<std::endl;
    
    if(node->children.size() == 0)
        return 0;
    std::vector<Node*>::iterator childrenItr;
    int highest=0;
    for(childrenItr = node->children.begin(); childrenItr != node->children.end(); childrenItr++){
        int height = getHeight(*childrenItr);
        if(height > highest)
            highest = height;
    }

    return highest + 1;

}
