#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>

class Node{
    public:
        int size;
        int val;
        Node* leftChild;
        Node* rightChild;
        Node(int val){
            this->val = val;
            leftChild = NULL;
            rightChild = NULL;
        }
};


Node* merge(Node* first, Node* second);

int deleteNodewithIndex(Node* node, int index);

void treeCheck(Node* node);

Node* constructTree(int start, int end);

bool cache[50000];

int main(){
    int inputNum;
    std::vector<int> stack;
    std::deque<int> queue;
    std::cin>>inputNum;

    Node* root = constructTree(0,inputNum-1);
    stack.reserve(inputNum);
    deque.reserve(inputNum);

    for(int i=0; i<inputNum; i++){
        int input;
        std::cin>>input;
        stack.push_back(input);
        cache[i] = false;
    }

    while(stack.size() > 0){
        int deleted = deleteNodewithIndex(stack.size() - stack.back());
        stack.pop_back();
        queue.push_back(deleted);
    }

    while(queue.size() > 0){
        std::cout<<queue.front()<<" ";
        queue.pop_front();
    }

}


Node* constructTree(int start, int end){
    int index = (start + end)/2;
    currentNode->val index;

    if(start+1 == end){
        if(cache[index] == false){
            Node* node = new Node(index);
            node->size = 1;
            return node;
        }
        else if(cache[index] == true && cache[index+1] == false){
            Node* node = new Node(index+1);
            node->size = 1;
            return node;
        }
        else 
            return NULL;
    }

    if(start == end && cache[index] == false){
        Node* node = new Node(index);
        node->size = 1;
    }

    Node* currentNode = new Node*(index);

    currentNode->leftChild = constructTree(start, index);
    currentNode->rightChild = constructTree(index + 1, end);

    int leftSize = 0, rightSize = 0;

    if(currentNode->leftChild != NULL){
        leftSize = currentNode->leftChild->size;
    }
    if(currentNode->rightChild != NULL){
        rightSize = currentNode->rightChild->size;
    }

    currentNode->size = leftSize + rightSize + 1;

    return currentNode;
}

void treeCheck(Node* node){
    if(node == NULL)
        return;

    treeCheck(node->leftChild);
    std::cout<<node->val<<" ";
    treeCheck(node->rightChild);

    return;
}


int deleteNodewithIndex(Node* node, int index){//returns tree with according index deleted
    if(node == NULL) // return NULL if node was NULL
        return -1;
    if(index > node->size || index < 0) // invalid index
        return -1;

    int deletedVal = -1;

    if(node->leftChild->size > index){
        node->size -= 1;
        deletedVal = deleNodewithIndex(node->leftChild, index);
    }
    else if(node->leftChild->size == index){ // deletes itself
        Node* left = node->leftChild;
        Node* right = node->rightChild;
        deletedVal = node->val;
        int size = node->size;
        delete node;
        node = merge(left, right);
    }
    else if(node->rightChild->size < index){
        node->size -= 1;
        deletedVal = deleteNodewithIndex(node->rightChild, index - node->leftChild->size);
    }

    return deletedVal;
}


Node* merge(Node* first, Node* second){
    if(first == NULL)
        return second;
    if(second == NULL)
        return first;

    if(first->val > second->val)
        first->left = merge(first->left, second);
    if(second->val > first->val)
        first->right = merge(first->right, second);

    int leftSize = 0, rightSize = 0;
    if(first->left != NULL){
        leftSize = first->left->size;
    }
    if(first->right != NULL){
        rightSize = first->right->size;
    }
    first->size = leftSize + rightSize + 1;
    return first;
}

