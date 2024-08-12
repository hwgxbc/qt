#include <iostream>
#include <locale>
#include <wchar.h>

int main() {
    // 设置本地化以支持宽字符
    std::setlocale(LC_ALL, "");

    // 使用 wchar_t 类型定义一个宽字符串
    wchar_t wstr[] = L"你好，世界！";

    // 在 C++ 中打印宽字符串
    std::wcout << wstr << std::endl;

    return 0;
}
