#include "Fraction.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 测试构造函数
    Fraction f1(3, 4); // 3/4
    Fraction f2(5, 6); // 5/6
    Fraction f3;       // 默认构造函数
    Fraction f4(f1);   // 拷贝构造函数

    cout << "Testing constructors:" << endl;
    cout << "f1: " << f1 << endl;
    cout << "f2: " << f2 << endl;
    cout << "f3 (default): " << f3 << endl;
    cout << "f4 (copy of f1): " << f4 << endl;

    // 测试算术运算符
    cout << "\nTesting arithmetic operators:" << endl;
    cout << "f1 + f2 = " << (f1 + f2) << endl;
    cout << "f1 - f2 = " << (f1 - f2) << endl;
    cout << "f1 * f2 = " << (f1 * f2) << endl;
    cout << "f1 / f2 = " << (f1 / f2) << endl;

    // 测试关系运算符
    cout << "\nTesting relational operators:" << endl;
    cout << "f1 < f2: " << (f1 < f2) << endl;
    cout << "f1 <= f2: " << (f1 <= f2) << endl;
    cout << "f1 == f2: " << (f1 == f2) << endl;
    cout << "f1 != f2: " << (f1 != f2) << endl;
    cout << "f1 >= f2: " << (f1 >= f2) << endl;
    cout << "f1 > f2: " << (f1 > f2) << endl;

    // 测试类型转换
    cout << "\nTesting type conversions:" << endl;
    double f1_as_double = static_cast<double>(f1);
    string f1_as_string = static_cast<string>(f1);
    cout << "f1 as double: " << f1_as_double << endl;
    cout << "f1 as string: " << f1_as_string << endl;

    // 测试流操作符
    cout << "\nTesting stream operators:" << endl;
    Fraction f5;
    cout << "Enter a fraction (format: numerator/denominator): ";
    cin >> f5;
    if (cin.fail()) {
        cout << "Invalid fraction input!" << endl;
    } else {
        cout << "You entered: " << f5 << endl;
    }

    // 测试 simplify 函数
    cout << "\nTesting simplify function:" << endl;
    Fraction f6(8, 12); // 8/12
    cout << "f6 before simplify: " << f6 << endl;
    cout << "f6 after simplify: " << f6.simplify() << endl;

    // 测试 fromString 静态函数
    cout << "\nTesting fromString function:" << endl;
    try {
        Fraction f7 = fromString("7/9");
        cout << "Fraction from string '7/9': " << f7 << endl;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    // 测试析构函数（通过程序结束自动调用）
    cout << "\nTesting destructor (will be called automatically at the end of the program)." << endl;

    return 0;
}