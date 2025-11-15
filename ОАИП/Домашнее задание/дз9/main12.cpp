#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;
int main(){
    vector<string> logs = { "INFO: Start", "ERROR: Disk failure", "WARNING: Low memory", "ERROR: Disk failure", "INFO: Stop" };
    shared_ptr<vector<string>> pLogs = make_shared<vector<string>>(logs); //(logs) - это аргумент конструктора вектора
    
    cout << "Исходный журнал: ";
    for_each((*pLogs).begin(), (*pLogs).end(), [](const string& x) { cout << x << " "; });
    cout << endl;
    
    shared_ptr<vector<string>> pErrors = make_shared<vector<string>>();
    
    copy_if(pLogs->begin(), pLogs->end(), back_inserter(*pErrors), //-> здесь нужны потому, что pLogs - это указатель на вектор, а не сам вектор.
            [](const string& s) { return s.find("ERROR") != string::npos; }); // если true то копируется в pErrors
    
    sort(pErrors->begin(), pErrors->end()); // unique без sort не рабоатет 
    auto last = unique(pErrors->begin(), pErrors->end()); //перемещает дубликат в конец, после всего выдает в last указатель на последний не дубликат 
    pErrors->erase(last, pErrors->end());
    
    cout << "Ошибки: ";
    for_each(pErrors->begin(), pErrors->end(), [](const string& x) { cout << x << " "; });
    cout << endl;
    return 0;
}