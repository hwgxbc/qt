#include <iostream>
#include <locale>
#include <wchar.h>

int main() {
    // ���ñ��ػ���֧�ֿ��ַ�
    std::setlocale(LC_ALL, "");

    // ʹ�� wchar_t ���Ͷ���һ�����ַ���
    wchar_t wstr[] = L"��ã����磡";

    // �� C++ �д�ӡ���ַ���
    std::wcout << wstr << std::endl;

    return 0;
}
