#include <iostream>
using namespace std;

class Account {
    private:
        int id;
        string name;
        int balance;

    public:
        Account(int _id, string _name) {
            this->id = _id;
            this->name = _name;
        }
        Account(int _id, string _name, int _balance) {
            this->id = _id;
            this->name = _name;
            this->balance = _balance;
        }

        int getId() {
            return id;
        }

        void setName(string _name) {
            this->name = _name;
        }

        string getName() {
            return name;
        }

        void deposit(int amount) {
            if (amount > 0) {
                this->balance += amount;
            }
        }

        void withdraw(int amount) {
            if (amount > this->balance) {
                cout << "Insufficient balance" << endl;
            } else {
                this->balance -= amount;
            }
        }

        int getBalance() {
            return this->balance;
        }

        void display() {
            cout << "Id: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Balance: " << balance << endl;
        }
};

int main() {
    Account account1(1000, "Tuan", 2000);
	account1.display();
	account1.withdraw(2100);
	account1.deposit(600);
	cout << "Balance: " << account1.getBalance() << endl;
	account1.withdraw(2100);
	cout << "Balance: " << account1.getBalance() << endl;
	return 0;
}