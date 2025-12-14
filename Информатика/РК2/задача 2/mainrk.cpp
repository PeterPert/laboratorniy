#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;
class BankAccount {
protected:
    string accountNumber;
    string ownerName;
    double balance;

bool isValidBalance(double amount) const {
        return amount >= 0;
    }

public:
    BankAccount(const string& accNumber, const string& owner, double initialBalance = 0.0) {
        accountNumber = accNumber;
        ownerName = owner;
        if (isValidBalance(initialBalance)) {
            balance = initialBalance;
            cout << "Счет создан для " << ownerName 
                 << " (№" << accountNumber 
                 << ") с балансом " << balance << " руб."<<endl;
        } else {
            balance = 0.0;
            cout << "Внимание: начальный баланс не может быть отрицательным." << endl;
        }
    }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: сумма пополнения должна быть положительной" << endl;
            return false;
        }
        balance += amount;
        cout << "Успешно пополнено на " << amount << " руб." << endl;
        cout << "Новый баланс: " << balance << " руб."<< endl;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: сумма снятия должна быть положительной"<< endl;
            return false;
        }
        
        if (amount > balance) {
            cout << "Ошибка: недостаточно средств на счете"<< endl;
            return false;
        }
        
        balance -= amount;
        cout << "Успешно снято " << amount << " руб."<< endl;
        return true;
    }
   
    string getAccountNumber() const {
        return accountNumber;
    }

    string getOwnerName() const {
        return ownerName;
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate; 

public:
    SavingsAccount(const string& accNumber, const string& owner, 
                   double initialBalance = 0.0, double rate = 0.0): BankAccount(accNumber, owner, initialBalance), interestRate(rate) {
        if (rate < 0) {
            interestRate = 0.0;
            cout << "Внимание: процентная ставка скорректирована до 0% " << endl;
        }
    }

    void addInterest() {
        if (interestRate > 0 && balance > 0) {
            double interest = balance * (interestRate / 100.0);
            balance += interest;
            cout << "Ставка: " << interestRate << "%, Новый баланс: " << balance << " руб." << endl;
        } 
        else {
            cout << "Проценты не начислены " << endl;
        }
    }

    double getInterestRate() const {
        return interestRate;
    }

    void setInterestRate(double rate) {
        if (rate >= 0) {
            interestRate = rate;
            cout << "Процентная ставка установлена: " << interestRate << "%" << endl;
        } else {
            cout << "Ошибка: процентная ставка не может быть отрицательной" << endl;
        }
    }
};

int main() {
    BankAccount account1("1234567890", "Иванов И.И.", 1000.0);
    account1.deposit(500.0);      
    account1.withdraw(300.0);     
    account1.withdraw(2000.0);

    SavingsAccount savings("0987654321", "Петров П.П.", 2000.0, 5.0);
    
    savings.deposit(1000.0);           
    savings.addInterest();             
    savings.withdraw(500.0);           
    savings.setInterestRate(7.5);      
    savings.addInterest();             
    
    cout << "Обычный счет: " << account1.getBalance() << " руб" << endl;
    cout << "Сберегательный счет: " << savings.getBalance() << " руб" << endl;
    return 0;
}


