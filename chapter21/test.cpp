#include <iostream>
#include <vector>

int main(){

    std::vector<int> *vect = new std::vector<int>;

    vect->push_back(1);
    vect->push_back(2);
    vect->push_back(3);

    for(int i=0; i<vect->size(); i++)
        std::cout<<(*vect)[i]<<std::endl;
    delete vect;
}
