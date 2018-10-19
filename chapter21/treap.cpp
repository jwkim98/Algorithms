#include <iostream>
#include <cstdlib>
#include <deque>
#include <vector>
/*
   implementation of reversing insertion sort
   using self-implemented Tree
*/

class treapNode{
    public:
        int val;
        int priority;
        treapNode* leftChild;
        treapNode* rightChild;
        treapNode(int value, int priority):val(value), leftChild(NULL), rightChild(NULL){
            this->priority = priority;
        }

        int getSize(){
            int leftSize = 0;
            int rightSize = 0;
            if(leftChild != NULL){
                leftSize = leftChild->getSize();
            }
            if(rightChild != NULL){
                rightSize = rightChild->getSize();
            }

            return leftSize + rightSize + 1;
        }

        int getHeight(){
            int leftHeight = 0;
            int rightHeight = 0;

            //if both children don't exist, height is '0'
            if(leftChild == NULL && rightChild == NULL)
                return 0;

            if(leftChild != NULL){
                leftHeight = leftChild->getHeight();
            }
            if(rightChild != NULL){
                rightHeight = rightChild->getHeight();
            }

            //return larger height between two children with 1 added
            return ((leftHeight > rightHeight) ? leftHeight: rightHeight) + 1;
        }
};

inline int getRandom(){
    return rand()%50000;
}

treapNode* search(treapNode* node, int val);

treapNode* insert(treapNode* node, int val); 

treapNode* RightRotate(treapNode* node);

treapNode* LeftRotate(treapNode* node);

treapNode* deleteNode(treapNode* root, int val);

treapNode* searchByIndex(treapNode* root, int index);

void inorderCheck(treapNode * node);

void deleteTree(treapNode *root);

void eval();
//        std::cout<<"c"<<std::endl;

int main(){
    int numofExe;
    std::cin>>numofExe;
    for(int i=0; i<numofExe; i++)
        eval();

}
void eval(){

    int inputNum;
    std::cin>>inputNum;
    std::deque<int> result;
    std::vector<int> inputs;

    treapNode* root = NULL;

    inputs.reserve(inputNum);

    for(int i=0; i<inputNum; i++){
        root = insert(root, i);
    }

//    inorderCheck(root);
//    std::cout<<"\n"<<root->getSize()<<std::endl;

    for(int i=0; i<inputNum; i++){
        int input;
        std::cin>>input;
        inputs.push_back(input);
    }

    for(int i=0; i<inputNum; i++){
        int input = inputs.back();
        inputs.pop_back();
//        std::cout<<"root Size: "<<root->getSize()<<std::endl;
        treapNode* found = searchByIndex(root, root->getSize() - input - 1);
        if(found != NULL){
            // push the result to the inputs deque
            result.push_back(found->val);
            root = deleteNode(root, found->val);
        }
    }

    while(result.size() > 0){
        std::cout<<result.back() + 1<<" ";
        result.pop_back();
    }

    deleteTree(root);
    std::cout<<std::endl;
}

//Searches typical node with value
//returns NULL if node wasn't found
treapNode* search(treapNode* node, int val){

    if(node == NULL)
        return NULL;

    if(val > node->val){
        return search(node->rightChild, val);
    }

    if(val < node->val){
        return search(node->leftChild, val);
    }

    if(node->val == val)
        return node;
}

// node: tree to insert, returns treapnode with node inserted
treapNode* insert(treapNode* node, int val){
    if(node == NULL)
        return new treapNode(val, getRandom());

    if(val > node->val){
        node->rightChild = insert(node->rightChild, val);
        //once inserted, fix the tree to have right proiority order
        if(node->rightChild->priority > node->priority){
            node = LeftRotate(node);
        }
    }
    else if(val <= node->val){
        node->leftChild = insert(node->leftChild, val);
        //if priority is violated, rotate the tree
        if(node->leftChild->priority > node->priority){
            node = RightRotate(node);
        }
    }
    return node;
}

//Rotates the tree right 
/*
    newRoot->right = oldRoot
    oldRoot->Left = rightChild of newRoot
*/
treapNode* RightRotate(treapNode* node){
    if(node == NULL || node->leftChild == NULL)
        return node;
    treapNode* newRoot = node->leftChild;
    treapNode* newRootRight = newRoot->rightChild;
    newRoot->rightChild = node;
    node->leftChild = newRootRight;
    return newRoot;
}

//Rotates the tree left
/*
   newRoot->Left node
   oldRoot->Right = leftchild of newRoot
*/
treapNode* LeftRotate(treapNode* node){
    if(node == NULL || node->rightChild == NULL)
        return node;
    treapNode* newRoot = node->rightChild;
    treapNode* newRootLeft = newRoot->leftChild;
    newRoot->leftChild = node;
    node->rightChild = newRootLeft;
    return newRoot;
}

treapNode* deleteNode(treapNode* root, int val){
    if(root == NULL)
        return root;

    //Search for the value to delete
    if(root->val > val){
        root->leftChild = deleteNode(root->leftChild, val);
        return root;
    }
    if(root->val < val){
        root->rightChild = deleteNode(root->rightChild, val);
        return root;
    }

    //delete root

    treapNode* left = root->leftChild;
    treapNode* right = root->rightChild;

    if(left == NULL && right == NULL){
        delete root;
        return NULL;
    }
    if(left == NULL){
        delete root;
        return right;
    }
    if(right == NULL){
        delete root;
        return left;
    }


    if(left->priority > right->priority){
        root = RightRotate(root);
        root->rightChild = deleteNode(root->rightChild, val);
    }else{
        root = LeftRotate(root);
        root->leftChild = deleteNode(root->leftChild, val);
    }

    return root;
}

treapNode* searchByIndex(treapNode* root, int index){
    if(root == NULL){
        return NULL; // no according index
    }
    int leftSize = 0;

    if(root->leftChild != NULL){
        leftSize = root->leftChild->getSize();
    }

    if(leftSize < index){
        treapNode *found = searchByIndex(root->rightChild, index - (leftSize + 1));
        return found;
    }

    else if(leftSize == index){
        return root; // found!
    }

    else if(index < leftSize){
        treapNode* found = searchByIndex(root->leftChild, index);
        return found;
    }
}

void inorderCheck(treapNode * node){
    if(node == NULL)
        return;

    inorderCheck(node->leftChild);
    std::cout<<node->val<<" ";
    inorderCheck(node->rightChild);

    return;
}
//Deletes whole tree with postorder transversal
void deleteTree(treapNode *root){
    if(root == NULL)
        return;

    deleteTree(root->leftChild);
    deleteTree(root->rightChild);
    delete root;

    return;
}



