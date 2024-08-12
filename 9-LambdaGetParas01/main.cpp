#include <iostream>

using namespace std;

int main() {

    int x = 10;
    int y = 20;

    auto add = [x,y]()->int{
        //x++;
        //x = 15;���ַ�ʽ�����ǲ����޸ı���ֵ�ģ�ֻ�����ã��ɶ�
        return x + y;
    };

    int ret = add();
    cout << ret << endl;

    int z = 5;
    auto mul = [=]()->int{
        //x++;
        //x = 15;���ַ�ʽ�������б���������Ҫȥ���б���д�����ǲ����޸ı���ֵ�ģ�ֻ�����ã��ɶ�
        return x * y * z;
    };
    ret = mul();
    cout << ret << endl;

    //�����õķ�ʽ��������������ָ�룬���е�ַ����
    auto modifyAndMul = [&]()->int{
        //x++;
        x = 15; //���õķ�ʽ�������б����Ĳ��񣬿ɶ���д
        return x * y * z;
    };
    ret = modifyAndMul();
    cout << ret << endl;
    cout << "x=" << x << endl;

    return 0;
}
