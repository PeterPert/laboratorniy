#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;
struct order{
    string customername;
    vector<string> items;
};
void addOrder(queue<order>& orderQueue, const order& newOrder) {
    orderQueue.push(newOrder);
    cout << "Заказ от " << newOrder.customername << " добавлен." << endl;
}
void processOrder(queue<order>& orderQueue) {
    order current = orderQueue.front();
    cout << "\nОбработка заказа:" << endl;
    cout << "Клиент: " << current.customername << endl;
    cout << "Товары: ";
    for (size_t i = 0; i < current.items.size(); i++) {
        cout << current.items[i];
        if (i < current.items.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    orderQueue.pop();
    cout << "Очередь заказов пуста!" << endl;
}

int main(){
    queue<order> orders;
    order order1 = {"Иван Иванов", {"Ноутбук", "Мышь", "Сумка"}};
    order order2 = {"Мария Петрова", {"Смартфон", "Чехол"}};
    order order3 = {"Алексей Сидоров", {"Наушники"}};
    
    addOrder(orders, order1);
    addOrder(orders, order2);
    addOrder(orders, order3);
    processOrder(orders);
}