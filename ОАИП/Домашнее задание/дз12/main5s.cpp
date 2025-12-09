#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;
struct BankAccount {
    int accountNumber;
    string ownerName;
    double balance;
};
// Функция для поиска счета по номеру
BankAccount* findAccount(vector<BankAccount>& accounts, int accountNumber) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accountNumber) {
            return &acc;
        }
    }
    return nullptr;
}
int main() {
    vector<BankAccount> accounts;
    int choice;
    do {
        cout << "\nВыберите действие:\n"
             << "1. Создать новый банковский счет\n"
             << "2. Пополнить счет\n"
             << "3. Снять деньги со счета\n"
             << "4. Показать информацию о счете\n"
             << "5. Выйти\n"
             << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: {
                BankAccount newAccount;
                cout << "Введите номер счета: ";
                cin >> newAccount.accountNumber;
                cin.ignore();
                cout << "Введите имя владельца счета: ";
                getline(cin, newAccount.ownerName);
                newAccount.balance = 0.0; 
                accounts.push_back(newAccount);
                cout << "Банковский счет создан.\n";
                break;
            }
            
            case 2: {
                int accountNumber;
                cout << "Введите номер счета для пополнения: ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    double amount;
                    cout << "Введите сумму для пополнения: ";
                    cin >> amount;
                    
                    if (amount > 0) {
                        account->balance += amount;
                        cout << "Счет пополнен на " << amount << " рублей.\n";
                    } else {
                        cout << "Сумма должна быть положительной!\n";
                    }
                } else {
                    cout << "Счет с номером " << accountNumber << " не найден.\n";
                }
                break;
            }
            
            case 3: {
                int accountNumber;
                cout << "Введите номер счета для снятия: ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    double amount;
                    cout << "Введите сумму для снятия: ";
                    cin >> amount;
                    
                    if (amount > 0 && amount <= account->balance) {
                        account->balance -= amount;
                        cout << "Со счета снято " << amount << " рублей.\n";
                    } else if (amount > account->balance) {
                        cout << "Недостаточно средств на счете!\n";
                    } else {
                        cout << "Сумма должна быть положительной!\n";
                    }
                } else {
                    cout << "Счет с номером " << accountNumber << " не найден.\n";
                }
                break;
            }
            
            case 4: {
                int accountNumber;
                cout << "Введите номер счета для показа информации: ";
                cin >> accountNumber;
                
                BankAccount* account = findAccount(accounts, accountNumber);
                if (account != nullptr) {
                    cout << "Номер счета: " << account->accountNumber << "\n"
                         << "Имя владельца счета: " << account->ownerName << "\n"
                         << "Баланс: " << account->balance << " рублей\n";
                } else {
                    cout << "Счет с номером " << accountNumber << " не найден.\n";
                }
                break;
            }
            
            case 5:
                cout << "Программа завершена.\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while(choice != 5);
    return 0;
}