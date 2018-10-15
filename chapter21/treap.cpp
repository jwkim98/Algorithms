#include <iostream>

class treapNode{
    public:
        int val;
        int priority;
        Node* leftChild;
        Node* rightChild;
        Node(int value):val(value), leftChild(NULL), rightChild(NULL){

        }

        int getSize(){
            int leftSize = 0;
            int rightSize = 0;
            if(leftChlid != NULL){
                leftSize = leftChild->getSize();
            }
            if(rightChild != NULL){
                rightsize = rightChild->getSize();
            }
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
}

treapNode* search(treapNode* node, int val){

    if(node == NULL)
        return NULL;

    if(val > node->val){
        return search(treapNode* node->right, int val);
    }

    if(val < node->val){
        return search(treapNode* node->left, int val);
    }

    if(node->val == val)
        return node;
}

treapNode* insert(treapNode* node, int val){ // node: tree to insert, returns treapnode with node inserted
    if(node == NULL)
        return new treapNode(val);

    if(val > node->val){
        node->right = insert(node->right, val);
        if(node->right->priority > node->priority){
            node = LeftRotate(node);
        }
    }
    else if(val <= node->val){
        node->left = insert(node->left, val);
        //if priority is violated, rotate the tree
        if(node->left->priority > node->priority){
            node = RightRotate(node);
        }
    }

    return node;
}

treapNode* RightRotate(treapNode* node){
    if(node == NULL || node->leftChild == NULL)
        return node;
    treapNode* newRoot = node->leftChild;
    treapNode* newRootRight = newRoot->rightChild;
    newRoot->rightChild = node;
    node->leftChild = newRootRight;

}

treapNode* LeftRotate(treapNode* node){
    if(node == NULL || node->rightChild == NULL)
        return node;
    treapNode* newRoot = node->rightChild;
    treapNode* newRootLeft = newRoot->leftChild;
    newRoot->left = node;
    node->rightChild = newRootLeft;
}

treapNode* deleteNode(treapNode* root, int val){
    treapNode* toDelete = search(root, val);

    if(toDelete == NULL)
        return root;

    treapNode* left = toDelete->leftChild;
    treapNode* right = toDelete->rightChild;

    if(left == NULL && right == NULL){
        delete toDelete;
        toDelete = NULL;
        return root;
    }
    if(left == NULL){
        delete toDelete;
        toDelete = right;
        return root;
    }
    if(right == NULL){
        delete toDelete;
        toDelete = left;
        return root;
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
    if(root = NULL)
        return NULL; // no according index

    if(root->leftChild->getSize() < index){
        return searchByIndex(root->leftChild, index);
    }

    if(root->leftChild->getSize() == index){
        return root; // found!
    }

    if(root->rightChild->getSize() > index){
        return searchByIndex(root->rightChild, index);
    }
}



