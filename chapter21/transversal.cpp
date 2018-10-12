#include <iostream>
#include <vector>

class node{
    public:
        node* left;
        node* right;
        int num;
        node(int num){
            this->num = num;
            left = NULL;
            right = NULL;
        }
};

void postOrderTraversal(node* root);

node* constructTree(std::vector<int> *preorderArray, std::vector<int> *inorderArray);

bool isinLeftof(int isleft, int from, std::vector<int> *array);

int main(){

    int numInputs;
    std::cin>>numInputs;

    std::vector<int> *preorderArray = new std::vector<int>;
    std::vector<int> *inorderArray = new std::vector<int>;
    preorderArray->reserve(numInputs);
    inorderArray->reserve(numInputs);

    for(int i=0; i<numInputs; i++){
        int input;
        std::cin>>input;
        preorderArray->push_back(input);
    }

    for(int i=0; i<numInputs; i++){
        int input;
        std::cin>>input;
        inorderArray->push_back(input);
    }

    postOrderTraversal(constructTree(preorderArray, inorderArray));
    delete preorderArray;
    delete inorderArray;
}

void postOrderTraversal(node* root){
    if(root->left != NULL)
        postOrderTraversal(root->left);
    
    if(root->right != NULL)
        postOrderTraversal(root->right);
    std::cout<<root->num<<" ";
    delete root;
}


node* constructTree(std::vector<int> *preorderArray, std::vector<int> *inorderArray){
    node *root = new node((*preorderArray)[0]);
    node* ancestor;

    for(int i=1; i<preorderArray->size(); i++){
        bool isAllocated = false;
        ancestor = root;
        while(!isAllocated){
            //determine if node is in left or right of its ancestor
            if(isinLeftof((*preorderArray)[i], ancestor->num, inorderArray)){
                if(ancestor->left == NULL){
                    std::cout<<"left "<<(*preorderArray)[i]<<std::endl;
                    ancestor->left = new node((*preorderArray)[i]);
                    isAllocated = true;//if left of ancestor is empty, allocate
                }else
                    ancestor = ancestor->left;//if its already been allocated, move the ancestor
            }
            else{
                if(ancestor->right == NULL){
                    std::cout<<"right "<<(*preorderArray)[i]<<std::endl;
                    ancestor->right = new node((*preorderArray)[i]);
                    isAllocated = true;
                }else
                    ancestor = ancestor->right;
            }
        }
    }
    return root;
}

bool isinLeftof(int isleft, int from, std::vector<int> *array){
    bool foundIsleft = false;
    bool foundFrom = false;

    for(int i=0; i< array->size(); i++){
        if((*array)[i] == isleft) foundIsleft = true;
        if((*array)[i] == from) foundFrom = true;

        if(foundIsleft == true && foundFrom == false) // return true if left element was discovered first
            return true;
        if(foundIsleft == false && foundFrom == true)// return false if right element was discovered first
            return false;
    }
    return true; // if both of them wasn't found, or isleft == from
}
