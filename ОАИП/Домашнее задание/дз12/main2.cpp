#include <iostream>
#include <queue>
#include <string>
using namespace std;

void addToQueue(queue<string>& queue, const string& person) {
    queue.push(person);
    cout << person << " добавлен в очередь." << endl;
}

void processQueue(queue<string>& queue) {
    if (!queue.empty()) {
        string person = queue.front();
        queue.pop();
        cout << person << " обработан" << endl;
    } else {
        cout << "Очередь пуста." << endl;
    }
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
        addToQueue(pupil, per);
        break;
    }
} 