#include <iostream>
#include <vector>
#include <algorithm>

inline int first_child(int current)
{
    return 2*current + 1;
}

inline int second_child(int current)
{
    return 2*current + 2;
}

inline int parent(int current){
    return (current - 1)/2;
}

void reverse_heapify(std::vector<int>& content, int current)
{
    int parent_index = parent(current);
    if(parent_index == current) 
        return;
    
    if(content.at(parent_index) < content.at(current))
    {
        std::swap(content.at(parent_index), content.at(current));
        reverse_heapify(content, parent_index);
    }
}

void push(std::vector<int>& content, int to_push){
    content.push_back(to_push);
    reverse_heapify(content, content.size() - 1);
}

void heapify(std::vector<int>& content, int current)
{
    int left_child = first_child(current);
    int right_child = second_child(current);
    int max_index = current;

    if(left_child < content.size() && content.at(max_index) < content.at(left_child))
        max_index = left_child;
    
    if(right_child < content.size() && content.at(max_index) < content.at(right_child))
        max_index = right_child;

    if(max_index != current){
        std::swap(content.at(max_index), content.at(current));
        heapify(content, max_index);
    }
}

int pop(std::vector<int>& content)
{
    std::swap(content.at(0), content.at(content.size() - 1));
    int rtn = content.at(content.size() - 1);
    content.pop_back();
    heapify(content, 0);
    return rtn;
}

int main(){
    std::vector<int> vect = {23,645,2,12,436, 23432, 1, 9, 0, 23465, 71, 8796};
    std::vector<int> heap;

    for(auto elem : vect){
        push(heap, elem);
    }
    std::cout<<"heap_size: "<<heap.size()<<std::endl;

    while(heap.size() > 0)
    {
        std::cout<<pop(heap)<<" ";
    }
    return 0;
}