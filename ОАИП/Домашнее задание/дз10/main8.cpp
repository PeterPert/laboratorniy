#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ifstream File1("file1.txt");
    ifstream File2 ("file2.txt");
    string line1;
    string line2;
    bool res = true;
    while (getline(File1,line1)){
        if (!getline(File2,line2)) {
            res = false;
            cout << "неравны" <<endl;
            break;
        } 
        if (!(line1 == line2)){
            res = false;
            cout << "неравны" <<endl;
            break;
        }
    } 
    if (getline(File2,line2)) {
            res = false;
            cout << "неравны" <<endl;
    }
    File1.close();
    File2.close();
    if (res){
        cout << "равны" << endl;
    }
}