#include <iostream>
#include <vector>
#include <algorithm>

class Node{
    public: 
        int height;
        int val;
        Node* parent;
        Node* leftChild;
        Node* rightChild;
        Node(int val, Node* parent){
            this->val = val;
            this->parent = parent;
        }

        ~Node(){
            delete leftChild;
            delete rightChild;
        }
};

class Person{
    public:
        bool isChecked;
        int ramenNum;
        int solveNum;
        Person(int ramenNum, int solveNum){
            isChecked = false;
            this->ramenNum = ramenNum;
            this->solveNum = solveNum;
        }
};


Node* ConstructTreeRamen(Node* parent, std::vector<Person*> *list, const int start, const int end);

int checkTree(Node* node); 

bool checkFunc(Person* person1, Person* person2){
    return person1->ramenNum < person2->ramenNum;
}

int main(){
    int inputNum;
    std::cin>>inputNum;

    std::vector<Person*> *personList = new std::vector<Person*>;

    personList->reserve(inputNum);

    for(int i=0; i<inputNum; i++){
        int solveNum, ramenNum;
        std::cin>>solveNum>>ramenNum;
        personList->push_back(new Person(ramenNum, solveNum));
    }

    std::sort(personList->begin(), personList->end(), checkFunc);

    Node* root = ConstructTreeRamen(NULL, personList, 0, personList->size() - 1);
    checkTree(root);

    std::vector<Person*>::iterator itr;
    for(itr = personList->begin(); itr != personList->end(); itr++){
        delete *itr;
    }
    delete personList;
    delete root;

}

Node* ConstructTreeRamen(Node* parent, std::vector<Person*> *list, const int start, const int end){ // constructs binary search tree by ramen number
    int index = (start + end)/2;

    //special case for returning 'end' value
    if(start+1 == end && (*list)[start]->isChecked == true && (*list)[end]->isChecked == false)
        return new Node((*list)[end]->ramenNum, parent);

    if((*list)[index]->isChecked == true) // return NULL if index node has already added
        return NULL;

    Node* currentNode = new Node((*list)[index]->ramenNum, parent);
    (*list)[index]->isChecked = true;

    if(start==end){
        return currentNode;
    }

    currentNode->leftChild = ConstructTreeRamen(currentNode , list, start, index);
    currentNode->rightChild = ConstructTreeRamen(currentNode , list, index + 1, end);

    return currentNode;
}

int checkTree(Node* node){ // inorder transversal of the tree for checking the algorithm
    if(node == NULL)
        return 0;

    int leftHeight = checkTree(node->leftChild);
    std::cout<<node->val<<" ";
    int rightHeight = checkTree(node->rightChild);

    int height = ((leftHeight > rightHeight)? leftHeight: rightHeight) + 1;
    node->height = height;

    return height;
}

