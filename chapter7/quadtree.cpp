#include <iostream>
#include <cstring>

using namespace std;

struct node{
    public:
        char type;
        struct node *tl,*tr,*bl,*br;
        node(char type):type(type)
        {
            tl = NULL;
            tr = NULL;
            bl = NULL;
            br = NULL;
        }

        ~node(){
            if(type == 'x'){
                delete tl;
                delete tr;
                delete br;
                delete bl;
            }
        }
        
};

node* buildTree(char *str);

char* reverseTree(node* Tree);

int main(){
    char input[1000];
    cin>>input;
    node* tree= buildTree(input);

    char* ans = reverseTree(tree);
    cout<<ans<<endl;

    delete[] ans;
    delete tree;

}

node* buildTree(char* str){
    node* tree;
    static int index=0;
    char state = str[index];
    index+=1;
    
    tree = new node(state);
    tree->type = state;

    if(state == 'x'){
        tree->tl = buildTree(str);
        tree->tr = buildTree(str);
        tree->bl = buildTree(str);
        tree->br = buildTree(str);
    }

    return tree;

}

char* reverseTree(node* tree){
    static int index = 0;
    static char* str = new char[1000];
    str[index] = tree->type;
    index+=1;

    if(tree-> type == 'x'){
        reverseTree(tree->bl);
        reverseTree(tree->br);
        reverseTree(tree->tl);
        reverseTree(tree->tr);
    }

    return str;
}
