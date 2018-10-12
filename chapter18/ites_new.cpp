#include <iostream>
#include <queue>

const uint32_t mod = -1;

bool increment_tail(int *tail_index, std::queue<uint32_t> *signals, const int N, uint32_t *sum);

bool increment_head(int *head_index, int *tail_index, std::queue<uint32_t> *signals, const int N, uint32_t *sum);

uint32_t get_next(const std::queue<uint32_t> *signals);

int run(const int N, const int K);

int main(){
    int N;
    int K;
    std::cin>>N;
    std::cin>>K;

    uint32_t ans = run(N,K);
    std::cout<<ans<<std::endl;
}

int run(const int N, const int K){
    std::cout<<"called run"<<std::endl;
    int count = 0;
    int *tail_index = new int();
    int *head_index = new int();
    std::queue<uint32_t> *signals = new std::queue<uint32_t>;
    uint32_t *sum = new uint32_t();
    *sum = 1983;
    *tail_index = 0;
    *head_index = 0;
    std::cout<<"before_push: "<<std::endl;
    signals->push(1983);

    while(*head_index != *tail_index || *head_index < N){
        std::cout<<"sum: "<<*sum<<" tail_index: "<<*tail_index<<" head_index: "<<*head_index<<std::endl;
        if(*sum == K)
            count+=1;
        
        bool ok = true;
        while(*sum<K && ok && *tail_index < N){
            ok = increment_tail(tail_index, signals, N, sum);
        }
        while(*sum >= K && ok && *head_index < N){
            ok = increment_head(head_index, tail_index, signals,N, sum);
            if(*sum == K)
                break;
        }

        if(*sum < K && *tail_index > N-1)
            break;
    }
    delete signals;
    delete tail_index;
    delete head_index;
    delete sum;
    return count;
}

bool increment_tail(int *tail_index, std::queue<uint32_t> *signals, const int N, uint32_t *sum){
    std::cout<<"increment_tail: "<< *tail_index<<std::endl;
    if(*tail_index > N-1)
        return false;
    else{
        uint32_t next = get_next(signals);
        signals->push(next);
        *sum += next;
        *tail_index += 1;
        return true;
    }
}

bool increment_head(int *head_index, int *tail_index, std::queue<uint32_t> *signals, const int N, uint32_t *sum){
    std::cout<<"increment_head :"<<*head_index<<std::endl;
    if(*head_index >= *tail_index){

        bool ok = increment_tail(tail_index, signals, N, sum);
        if(ok == false)
            return false;

        uint32_t popped = signals->front();
        signals->pop();
        *sum -= popped;
        *head_index +=1;
        return true;
    }
    else{
        uint32_t popped = signals->front();
        signals->pop();
        *sum -= popped;
        *head_index +=1;
        return true;
    }
}

uint32_t get_next(const std::queue<uint32_t> *signals){
    uint32_t seed = signals->back();
   // return (seed*214013 + 2531011) % mod;
    return seed+1;
}
