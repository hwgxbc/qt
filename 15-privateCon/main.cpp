#include <iostream>
#include <string>

using namespace std;

/*
银行的账户是一个模板，是一个类，有存款人信息和账户额度，而具体的存款人视为一个对象，
一个对象不能私自修改账户额度，需要通过一个操作流程，比如去ATM或者柜台进行操作才能修改到账户额度，
所以，存款人信息和账户额度设计成私有权限，通过公有的操作流程，也就是公有函数去操作私有变量。
基于这个场景，我们编程实现代码
*/

class BankAccount{
private:
    //有存款人信息和账户额度
    string name;
    string addr;
    int age;
    double balance;
public:
    string bankAddr;
    //比如去ATM或者柜台进行操作才能修改到账户额度
    void registerMes(string newName, string newAddr,int newAge,double newBalance);
    void withdraw(double amount);
    void deposit(double amount);
    double getBalance();
    void printUserInfo();
};
void BankAccount::printUserInfo()
{
    string mesTem = "账户名：" + name + "，地址：" + addr +
            ",年龄："+ std::to_string(age) + ",存款：" + std::to_string(balance);
    cout << mesTem << endl;
}

void BankAccount::registerMes(string newName, string newAddr,int newAge,double newBalance)
{
    name = newName;
    addr = newAddr;
    age  = newAge;
    balance = newBalance;
}

// 存款方法
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        cerr << "Deposit amount must be positive." << endl;
    }
}
// 取款方法
void BankAccount::withdraw(double amount) {
    if (amount > balance) {
        cerr << "Insufficient funds." << endl;
    } else if (amount <= 0) {
        cerr << "Withdrawal amount must be positive." << endl;
    } else {
        balance -= amount;
    }
}

// 获取当前余额的方法
double BankAccount::getBalance() {
    return balance;
}

int main()
{
    BankAccount user1;
    user1.registerMes("老陈","深圳光明区",35,100);
    user1.printUserInfo();
    user1.deposit(1000);
    cout << user1.getBalance() << endl;
    user1.withdraw(30);
    cout << user1.getBalance() << endl;
    return 0;
}
