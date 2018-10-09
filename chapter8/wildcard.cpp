#include <iostream>
#include <cstring>

using namespace std;

char **str;
char *flag; //stores state of each string input 't', 'f', 'n'
int *idx; //index of each string
char wildcard[51];
int inputs;

void checkStrings();
void checkStringsA(char check);
void checkStringsB();
void checkStringsC(char check);


int main(){

    cin>>inputs;

    idx = new int[inputs];
    flag = new char[inputs];
    str = new char*[inputs];
    for(int i=0; i<inputs; i++){
        *(str+i) = new char[101];
        idx[i] = -1;
        flag[i] = 'n';
    }

    cout<<"wildcard"<<endl;
    cin>>wildcard;

    for(int i=0; i<inputs ;i++){
        cout<<" input: ";
        cin>>str[i];
    }

    checkStrings();

    for(int i=0; i<inputs; i++){
        if(flag[i] !='f')
            cout<<str[i]<<endl;
    }

    //free resources
    delete[] idx;
    delete[] flag;
    for(int i=0; i<inputs; i++)
        delete[] str[i];
    delete[] str;
}


void checkStrings(){
    for(int i=0; i< strlen(wildcard); i++){
        if(wildcard[i] == '*'){ // check until next character appears
            if(i+1 == strlen(wildcard))
                continue;
            if(wildcard[i+1] == '?' || wildcard[i+1] == '\0' || wildcard[i+1] == '*')
                continue;
            else{
                checkStringsA(wildcard[i+1]);
                i++;
            }
        }
        else if(wildcard[i] == '?'){
            checkStringsB();
        }
        else{
            checkStringsC(wildcard[i]);
        }
    }

}


void checkStringsA(char check){ //*
    for(int i=0;i<inputs; i++){
  //      cout<<"a"<<endl;
        if(flag[i] == 't' || flag[i] == 'f')
            continue;

        idx[i]++;
        if(str[i][idx[i]] == check){
            continue;
        }

        int indexwithCheck =-1;

        for(int count=0; count<strlen(str[i]); count++)
        {
            if(str[i][count] == check)
                indexwithCheck = count;
        }

        if(indexwithCheck == -1)
            flag[i] = 'f';

        idx[i] = indexwithCheck;
        

    }

}

void checkStringsB(){ //'?'
    for(int i=0; i<inputs; i++){
        if(flag[i] == 't' || flag[i] == 'f')
            continue;
        idx[i]++;
        if(idx[i] == strlen(str[i]))
            flag[i] = 'f';

    }
}

void checkStringsC(char check){ // normal character
    for(int i=0; i<inputs; i++){
        if(flag[i] == 't' || flag[i] == 'f')
            continue;
        idx[i]++;

        if(str[i][idx[i]] != check){
            flag[i] = 'f';
            continue;
        }

    }
}
