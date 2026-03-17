#include <iostream>
using namespace std;

int* bad_pointer() {
    int x = 10;
    return &x; // возврат адреса локальной переменной
}

int main() {
    int unused_var; // не используется

    int y; // не инициализирован
    if (y > 0) {
        cout << "y > 0" << endl;
    }

    int arr[3];
    arr[5] = 100; // выход за границы массива

    int* p = bad_pointer();
    cout << *p << endl; // использование висячего указателя

    int* mem = new int[5];
    mem[0] = 1;
    // утечка памяти: delete[] нет

    return 0;
}
// clang-tidy
// Cmd+Shift+P → Tasks: Run Task → Analyze active file (clang-tidy)