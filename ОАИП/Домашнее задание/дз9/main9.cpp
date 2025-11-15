#include <iostream>
#include <memory> 
#include <vector>
using namespace std;
void processA(shared_ptr<vector<int>> buf){
    for (int i = 0; i < 10; i++){
        (*buf)[i] = (*buf)[i] + 1; 
    }
    for (int i = 0; i < 10; i++){
        cout << (*buf)[i] << " "; 
    }
    cout << endl;
} 

void processB(shared_ptr<vector<int>> buf) {
    for (int i = 0; i < 10; i++){
        (*buf)[i] = (*buf)[i] * 2; 
    }
    for (int i = 0; i < 10; i++){
        cout << (*buf)[i] << " "; 
    }
    cout << endl;
}

int main(){
    shared_ptr<vector<int>> buffer = make_shared<vector<int>>(10);
    for (int i = 1; i < 11; i++){
        (*buffer)[i-1] = i; 
    }
    
    processA(buffer);
    processB(buffer);
    return 0;
}