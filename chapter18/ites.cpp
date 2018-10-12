#include <iostream>

const uint32_t mod = -1; // 2^32

class element{
    public:
        element* next = NULL;
        element* before = NULL;
        uint32_t value;
        element(uint32_t value){
            this->value = value;
        }
};

int run(element **head, element **tail, element **top,int N, uint32_t K);

bool incrementTail(element** tail, element* top, uint32_t *sum, int* position, int N);

bool decrementTail(element** tail, element* head, uint32_t* sum);

bool incrementHead(element** head, element* top, uint32_t* sum);



int main(){
    element* head, *tail, *top;
    int N;
    uint32_t K;
    std::cin>>N;
    std::cin>>K;

    int count = run(&head, &tail, &top, N, K); 
    std::cout<<count<<std::endl;

}

int run(element **head, element **tail, element **top,int N, uint32_t K){
    int count = 0;
    uint32_t sum;
    int position=1;
    *head = new element(1983);
    tail = head;
    top = tail;
    (*head)->next = NULL;
    sum = (*head)->value;

    bool isMore = true;
    while(isMore || position != N){
        std::cout<<"position: "<<position<<std::endl;
        while(sum > K){
            bool ok = decrementTail(tail,*head,&sum);

        std::cout<<"sum: "<< sum <<std::endl;
        std::cout<<"tail: "<<(*tail)->value<<std::endl;
            if(sum == K){
                count++;
                incrementTail(tail,*top,&sum,&position,N);
                break;
            }
            if(ok == false){
                incrementTail(tail,*top,&sum,&position,N);
                break;
            }
        }

        while(sum <= K){
            bool ok = incrementTail(tail,*top,&sum,&position,N);
            if(sum == K){
                count++;
                break;
            }
            if(ok == false)
                break;
        }

        isMore = incrementHead(head,*top,&sum);
    }
    return count;
}


bool incrementTail(element** tail, element* top, uint32_t *sum, int* position, int N){
    if((*tail)->next == NULL){
        if(*position < N){
            (*tail)->next = new element((((*tail)->value))%10000 + 1);
            top = (*tail)->next;
            top->before  = *tail; //reset the top of the queue
            *tail = top;
            (*sum) += (*tail)->value;
            (*position)++;
            std::cout<<"pos: "<<*position<<std::endl;
            return true;
        }
        return false;
    }

    (*tail) = (*tail)->next;
    (*sum) += (*tail)->value;
    return true;
}

bool decrementTail(element** tail, element* head, uint32_t* sum){
    if(head == *tail)//head must be the first
        return false;
    (*tail) = (*tail)->before;
    (*sum) -= (*tail)->value;
    return true;
}

bool incrementHead(element** head, element* top, uint32_t* sum){
    if(*head == top)//top must be the last
        return false;
    element* temp = *head;
    (*sum) -= (*head)->value;
    delete[] *head; //head
    *head = temp->next;
    return true;
}
