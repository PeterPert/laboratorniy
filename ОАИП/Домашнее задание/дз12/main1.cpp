#include <iostream>
#include <queue>
#include <string>
using namespace std;
void processQueue(queue<string> queue) {
    int i = 1;
    while(!queue.empty()){
        cout << "обработан:" << queue.front() << endl;
        queue.pop();
    }
    cout << "очередь пуста" << endl;
}
void addtoqueue(queue<string>& queue, string &person) {
    queue.push(person);
    cout << "добавлен:" << person<< endl;
}
int main() {
    queue<string> pupil;
    pupil.push("Иванов");
    pupil.push("Петров");
    pupil.push("Сидоров");
    cout << "1 - обработка 2 - добавление" << endl;
    int n;
    cin >> n;
    switch (n) {
    case 1:
        processQueue(pupil);
        break;
    case 2:
        cin.ignore();
        string per;
        getline(cin, per);
        addtoqueue(pupil, per);
        break;
    }
} 