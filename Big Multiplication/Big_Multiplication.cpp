/*
* Name: Maiqi Hou
* Homework 2.1
* Tittle: Big Multiplication
* Due Date: 6.14
*
* This is Big value to multiple, so using the 
* string type. I create three examples, first 
* one two big positive numbers multiplication. 
* Second, One big positive and One big negative
* number multiplication.Last, two big negative numbers
* multiplication.
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
//For multiply 10^n, T(n) = O(n)
string multi10(string a, int n) {
    if (a != "0") {
        char i = '0';
        while (n > 0) {
            a += i;
            n--;
        }
    }
    return a;
}
//For balance two string, T(n) = 0(n)
void Trim(string &a, string &b) {
    int n1 = a.length();
    int n2 = b.length();
    if (n2 < n1)
        for (int i = 0; i < n1 - n2; i++)
            b.insert(0, "0");
    else if (n1 < n2)
        for (int i = 0; i < n2 - n1; i++)
            a.insert(0, "0");
}

//for substraction, T(n) = O(n)
string sub(string a, string b) {
    int n1 = a.length();
    int n2 = b.length();
    int x, y = 0;
    int borrow = 0;
    int s = 0;
    string subst;
    if (n1 < n2)
        swap(a, b);
    Trim(a,b);

    //main operation
    int i = a.length() - 1;
    while (i >= 0) {
        if ((x = a[i]-'0') < (y = b[i] - '0')) {
            if (borrow == 1)
                x -= 1;
                borrow = s / 10;
            s = (x + 10 - y)%10;
            borrow = 1;
        }
        else {
            if (borrow == 1)
                x -= 1;
                borrow = s / 10;
            s = x - y;
        }
        char n = '0' + s;
        subst.insert(0, 1, n);
        i--;
    }
    //elimate "0"
    char c = subst[0];
    bool t = false;
    while (c <= '0' && t == false) {
        subst.erase(0, 1);
        c = subst[0];
        if (subst[0] == '\0') {
            subst.insert(0, "0");
            t = true;
        }
    }
    return subst;
}

//For addition, T(n) = O(n)
string add(string a, string b) {
    string sum;
    int borrow = 0;
    Trim(a, b);
    int i = a.length() - 1;
    while (i >= 0) {
        int x = a[i] - '0';
        int y = b[i] - '0';
        int z = x + y + borrow;
        char n = '0' + (z % 10);
        sum.insert(0,1,n);
        borrow = z / 10;
        i--;

        if (i == -1 && borrow > 0)
            sum.insert(0, "1");
    }
    return sum;
}

string Karatsuba(string number1, string number2) {
    Trim(number1, number2);
    int i = number1.length();
    if (i < 3) {
        return to_string(stol(number1, nullptr, 10) * stol(number2, nullptr, 10));
    }

    int split = i / 2;
    string a = number1.substr(0, split);
    string b = number1.substr(split, i - split);
    string c = number2.substr(0, split);
    string d = number2.substr(split, i - split);

    string s1 = Karatsuba(a,c);  // a*c
    string s2 = Karatsuba(b,d);  // b*d
    string s3 = Karatsuba(add(a, b), add(c, d)); //(a + b) * (c + d)
    string s4 = sub(sub(s3, s2), s1); // step 3 - step 2 - step 1

    string result = add(add(multi10(s1, (i - split) * 2),s2), multi10(s4, i - split));
    return result;
}
int main() {
    cout << "**** Welcome Big Multiplication calculator ****" << endl;
    cout << endl;
    cout << "If you perfer enter two number, please enter (I)" << endl;
    cout << "If you perfer read file, please enter(R)" << endl;
    char c;
    char ch;
    cin >> c;
    string a, b;
    if (c == 'i' || c == 'I') {
        do {
            cout << "Please enter first number: ";
            cin >> a;
            cout << "Please enter second number: ";
            cin >> b;
            cout << endl;

            if (a[0] == '-' && b[0] == '-') {
                a.erase(0, 1);
                b.erase(0, 1);
                cout << "The result : " << Karatsuba(a, b) << endl;
            }
            else if (a[0] == '-' && b[0] != '-') {
                a.erase(0, 1);
                cout << "The result : " << "-" << Karatsuba(a, b) << endl;
            }
            else if (a[0] != '-' && b[0] == '-') {
                b.erase(0, 1);
                cout << "The result : " << "-" << Karatsuba(a, b) << endl;
            }else {
                cout << "The result : " << Karatsuba(a, b) << endl;
            }
            cout << endl;
            cout << "You want to do other mulitiplication? (Y/N)" << endl;
            cin >> ch;
        } while (ch != 'N' && ch != 'n');
    }
    else {
        string file_name;
        ifstream file;
        do {
            cout << "Please enter a file name: ";
            cin >> file_name;
            file.open(file_name.c_str());
            if (!file) {
                cout << "Sorry,we can't find your file" << endl;
            }
        } while (!file);
        file >> a;
        file >> b;
        cout << "Please enter first number: ";
        cout << a << endl;
        cout << "Please enter second number: ";
        cout << b << endl;
        cout << endl;
        if (a[0] == '-' && b[0] == '-') {
            a.erase(0, 1);
            b.erase(0, 1);
            cout << "The result : " << Karatsuba(a, b) << endl;
        }
        else if (a[0] == '-' && b[0] != '-') {
            a.erase(0, 1);
            cout << "The result : " << "-" << Karatsuba(a, b) << endl;
        }
        else if (a[0] != '-' && b[0] == '-') {
            b.erase(0, 1);
            cout << "The result : " << "-" << Karatsuba(a, b) << endl;
        }
        else {
            cout << "The result : " << Karatsuba(a, b) << endl;
        }
        file.close();
    }
    return 0;
}