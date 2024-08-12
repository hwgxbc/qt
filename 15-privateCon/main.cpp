#include <iostream>
#include <string>

using namespace std;

/*
���е��˻���һ��ģ�壬��һ���࣬�д������Ϣ���˻���ȣ�������Ĵ������Ϊһ������
һ��������˽���޸��˻���ȣ���Ҫͨ��һ���������̣�����ȥATM���߹�̨���в��������޸ĵ��˻���ȣ�
���ԣ��������Ϣ���˻������Ƴ�˽��Ȩ�ޣ�ͨ�����еĲ������̣�Ҳ���ǹ��к���ȥ����˽�б�����
����������������Ǳ��ʵ�ִ���
*/

class BankAccount{
private:
    //�д������Ϣ���˻����
    string name;
    string addr;
    int age;
    double balance;
public:
    string bankAddr;
    //����ȥATM���߹�̨���в��������޸ĵ��˻����
    void registerMes(string newName, string newAddr,int newAge,double newBalance);
    void withdraw(double amount);
    void deposit(double amount);
    double getBalance();
    void printUserInfo();
};
void BankAccount::printUserInfo()
{
    string mesTem = "�˻�����" + name + "����ַ��" + addr +
            ",���䣺"+ std::to_string(age) + ",��" + std::to_string(balance);
    cout << mesTem << endl;
}

void BankAccount::registerMes(string newName, string newAddr,int newAge,double newBalance)
{
    name = newName;
    addr = newAddr;
    age  = newAge;
    balance = newBalance;
}

// ����
void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        cerr << "Deposit amount must be positive." << endl;
    }
}
// ȡ���
void BankAccount::withdraw(double amount) {
    if (amount > balance) {
        cerr << "Insufficient funds." << endl;
    } else if (amount <= 0) {
        cerr << "Withdrawal amount must be positive." << endl;
    } else {
        balance -= amount;
    }
}

// ��ȡ��ǰ���ķ���
double BankAccount::getBalance() {
    return balance;
}

int main()
{
    BankAccount user1;
    user1.registerMes("�ϳ�","���ڹ�����",35,100);
    user1.printUserInfo();
    user1.deposit(1000);
    cout << user1.getBalance() << endl;
    user1.withdraw(30);
    cout << user1.getBalance() << endl;
    return 0;
}
