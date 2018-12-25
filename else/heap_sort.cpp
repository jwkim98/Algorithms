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

void heapify(std::vector<int>& to_sort, int heap_size, int root_index)
{
    int max_index = root_index;
    int first_child_index = first_child(root_index);
    int second_child_index = second_child(root_index);


    if(first_child_index < heap_size && to_sort.at(max_index) < to_sort.at(first_child_index))
    {
        max_index = first_child_index;
    }

    if(second_child_index < heap_size && to_sort.at(max_index) < to_sort.at(second_child_index))
    {
        max_index = second_child_index;
    }

    if(max_index != root_index)
    {
        std::swap(to_sort.at(root_index), to_sort.at(max_index));
        heapify(to_sort, heap_size, max_index);
    }
}

void heap_sort(std::vector<int>& to_sort, int heap_size)
{
    /// heap_size/2 - 1 is the first index for this 
    for(int index = heap_size/2 - 1; index >= 0; index--)
    {
        heapify(to_sort, heap_size, index);
    }

    for(int index = heap_size - 1; index >= 0; index--)
    {
        std::swap(to_sort.at(0), to_sort.at(index));
        heapify(to_sort, index, 0);
    }

}

int main()
{
    std::vector<int> vect = {12, 11, 13, 5, 6, 7, 2987, 23, 1, 239874, 9823, 438, 928, 1, 0, 23261843, 23, 75, 23, 25657,987,45,7654,72,756};
    heap_sort(vect, vect.size());
    
    for(std::vector<int>::iterator itr = vect.begin(); itr != vect.end(); itr++){
        std::cout<<*itr<<" ";
    }
}