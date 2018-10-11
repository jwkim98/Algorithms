#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int* quantization(int from, int to, int count);
int* minvalue(int from, int to);

int*** cache;

vector<int> num;

int main(){

    int numSize;
    int keySize;
    cin>>numSize; //number of input numbers
    num.reserve(numSize); //number of quantization keys
    cin>>keySize;

    cache = new int**[numSize];
    for(int i=0; i<numSize; i++)
        cache[i] = new int*[keySize];

    for(int i=0; i<numSize; i++)
        for(int j=0; j<keySize; j++)
            cache[i][j]=NULL;

    for(int i=0; i<numSize; i++){
        int input;
        cin>>input;
        num.push_back(input);
    }

    sort(num.begin(), num.end());

    int* ansArray = quantization(0,numSize-1,keySize);
    cout<<ansArray[0]<<endl;
    cout<<"quantized: ";
    for(int i=0; i<numSize; i++)
        cout<<ansArray[i+1]<<" ";

    for(int i=0;i<numSize; i++)
        delete[] cache[i];
    delete[] cache;

    delete[] ansArray;
}



int* quantization(int from, int to, int count){ // returns mean value 
    int* info = new int[to-from+1 +1]; // index 0 is always minimum root mean value
  
    if(count == 0 || from == to){
        int *thisMin = minvalue(from,to);
        for(int i=0; i<(to-from+2); i++)
            info[i] = thisMin[i];
        delete[] thisMin;
        return info;
    }

    if(cache[from][count] != NULL){ // if cache isn't empty, use cache
        for(int i=0; i<(to-from+2); i++)
            info[i] = cache[from][count][i];
        return info;
    }

    int min = INF;
    for(int i=from+1; i<to; i++){
        int *thisMin = minvalue(from , i);
        int *afterMin = quantization(i+1, to, count-1);
        int val = thisMin[0] + afterMin[0];
        if(val < min){
            min = val;
            info[0] = min;
            for(int j=1; j< (i-from+2); j++)
                info[j] = thisMin[j];
            
            for(int j= (i-from+2); j< (to-from+2); j++)
                info[j] = afterMin[j-(i-from+1)];
        }

        delete[] thisMin;
        delete[] afterMin;
    }

    for(int i=0; i<(to-from+2); i++)
        cache[from][count][i] = info[i];

    return info;
}

int* minvalue(int from, int to){
    int* info = new int[from-to+2];
    int sum = 0;
    for(int i=from; i<=to; i++)
        sum += num[i];

    float minKeyfloat = (float)sum/(float)(to-from+1);
    int minKey = (int)abs(minKeyfloat);
    minKey = (minKeyfloat - minKey > 0.5)? (minKey+1): minKey;

    int minvalue=0;
    for(int i=from; i<to; i++)
        minvalue += (int)pow((double)(num[i]-minKey),2.0); 

    info[0] = minvalue;
    for(int i=1; i<(to-from+2); i++)
        info[i] = minKey;
}
