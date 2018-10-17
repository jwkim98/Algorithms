#include <iostream>
#include <deque>

/*
    Heap sort Algorithm implemented with self-implemented max heap
*/
class maxHeap{
    private:
        const int INF = 98765;
        std::deque<int> data;
        unsigned int size = 0;

        void setInsert(unsigned int index){
            if(index == 0)
                return; //return if root (has no parent)

            int parentVal = data[(index - 1)/2];// parent of this node
            if(parentVal < data[index]){ // if parent value is smaller, swap the value with parent 
                int temp = data[index];
                data[index] = parentVal;
                data[(index-1)/2] = temp;

                setInsert((index-1)/2);// do the same thing with the parent index
            }
            return;
        }

        void setPop(unsigned int index){
            if(index > size - 1)
                return;
            if(index*2 + 1 > (size-1)) //if both children doesn't exist
                return;
            if(index*2 + 2 > (size-1)){ // if only left child exsists
                if(data[index*2 + 1] > data[index]){ // check if left child is larger than parent
                    int temp = data[index]; // if it is, swap the value..
                    data[index] = data[index*2 + 1];
                    data[index*2 + 1] = temp;
                    setPop(index*2 + 1); // and do the same thing with swapper parent
                }
                return;
            }


            if(data[index*2 + 1] <= data[index] && data[index*2 + 2] <= data[index]){
                return; // if parent(index) isn' smaller than both chldren, return
            }
            int temp = data[index];

            if(data[index*2 +1] > data[index*2 + 2]){ // if left child is larger, swap between parent
                data[index] = data[index*2 + 1];
                data[index*2 + 1] = temp;
                setPop(index*2 + 1); // do the same thng with left child
            }else{ // if right child is larger, swap between parent
                data[index] = data[index*2 + 2];
                data[index*2 + 2] = temp;
                setPop(index*2 + 2); // do the same thing with right child
            }

            return;
        }

    public:
        void insert(int val){
            size ++;
            if(data.size() < size)
                data.push_back(0);

            data[size - 1] = val;
            int index = size - 1;
            setInsert(index);
        }

        int pop(){
            if(size <= 0)
                return -INF;
            int root = data[0];
            data[0] = data[size-1];
            size--;
            setPop(0);
            return root;
        }

        int getVal(unsigned int index){
            return data[index];
        }
        
        int getSize(){
            return size;
        }
};


int main(){

    int inputNum;
    std::cin>>inputNum;

    maxHeap heap;
    
    for(int i=0; i<inputNum; i++){
        int input;
        std::cin>>input;
        heap.insert(input);
    }

    for(int i=0; i<heap.getSize(); i++){
        std::cout<<heap.getVal(i)<<" ";
    }
    std::cout<<std::endl;

    while(heap.getSize() > 0){
        std::cout<<heap.pop()<<" ";
    }
}
