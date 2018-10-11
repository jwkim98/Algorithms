#include <iostream>

class element{
    public:
        int num;
        bool alive = true;
        element* next = NULL;
        element* before = NULL;
        element(int num){
            this->num = num;

        }

};

void getNext(element** current, int stride);


int main(){

    int numPeople;
    int stride;

    std::cin>>numPeople;
    std::cin>>stride;

    element *first = new element(1);
    element *ptr = first;
    for(int i=2; i<=numPeople; i++){
        ptr->next = new element(i);
        ptr = ptr->next;
    }
    element *last = ptr;
    ptr->next = first;
    ptr = ptr->next; // go back to first

    int count = numPeople;

    ptr->alive = false;//kill first one
    count--;
    getNext(&ptr, stride);
    while(ptr->num != 1 && count > 2){
       // std::cout<<"a"<<std::endl;
        ptr->alive = false;
        count--;
        getNext(&ptr,stride);
    }

    ptr=first;
    for(int i=0; i<numPeople; i++){
        if(ptr->alive == true)
            std::cout<<ptr->num<<" ";
        ptr = ptr->next;
    }

    ptr=first->next;
    for(int i=2; i<=numPeople; i++){
        element *next = ptr->next;
        delete[] ptr;
        ptr = next;
    }
    delete first;
}

void getNext(element** current, int stride){
    for(int i=0; i<stride; i++){
        *current = (*current)->next;
    }
}
