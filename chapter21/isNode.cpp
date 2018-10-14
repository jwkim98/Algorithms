#include <iostream>
#include <vector>
#include <Algorithm>

class Node{
    public: 
        int height;
        int depth;
        int val;
        Node* parent;
        Node* leftChild;
        Node* rightChild;
        Node(int val, Node* parent){
            this->val = val;
            this->depth = depth;
            this->parent = parent;
        }

        ~Node(){
            delete leftchild;
            delete rightchild;
        }
};

class Person{
    public:
        bool isChecked;
        int ramenNum;
        int solveNum;
        person(int ramenNum, int solveNum){
            isChecked = false;
            this->ramenNum = ramenNum;
            this->solveNum = solveNum;
        }
};


Node* ConstructTree(Node* parent, std::vector<Person*> *list, const int start, const int end);

void checkTree(Node* node); 

int main(){
    int inputNum;
    std::cin>>inputNum;

    std::vector<Person> personList;

    ramenList.reserve(inputNum);
    solveList.reserve(inputNum);

    for(int i=0; i<inputNum; i++){
        int solveNum, ramenNum;
        std::cin>>solveNum>>ramenNum;
        ramenList.push_back(new Person(ramen, solve));
    }

    std::sort(ramenList.begin(), ramenList.end());
    std::sort(solveList.begin(), solveList.end());
    int ramenStartIndex = ramenList.size()/2;
    int solveStartIndex = solveList.size()/2;

    Node* root = ConstructTree(NULL, personList, 0, personLit.size());
    checkTree(root);

    std::vector<Person>::iterator itr;
    for(itr = personList.begin(); itr != personList.end(); itr++){
        delete *itr;
    }
    delete itr;
    delete root;

}

Node* ConstructTree(Node* parent, std::vector<Person*> *list, const int start, const int end){ // constructs binary search tree
    index = (start + end)/2;

    //special case for returning 'end' value
    if(start+1 == end && (*list)[start] == true && (*list)[end] == false)
        return new Node((*list)[end]->ramenNum, parent);

    if((*list)[index]->isChecked == true) // return NULL if index node has already added
        return NULL;

    currentNode = new Node((*list)[index]->ramenNum, parent);
    (*list)[index]->isChecked = true;

    if(start==end){
            return currentNode;
    }

    currentnode->leftChild = ConstructTree(currentNode , list, start, index);
    currentnode->rightChild = ConstructTree(currentNode , list, index + 1, end);

    return currentNode;
}

void checkTree(Node* node){ // inorder transversal of the tree for checking the algorithm
    if(node == NULL)
        return 0;

    int leftHeight = checkTree(node->leftChild);
    std::cout<<node->val<<" ";
    int rightHeight = checkTree(node->rightChild);

    return ((leftHeight > rightHeight)? leftHeight, rightHeight) + 1;
}
