#include "main.h" // заголовочный файл

short counter = -1; // firstly for first file0.txt we need to give a var -1

int main()
{
    cout << "This is a simple calculator!\n"; // start of programm
    char command = ' ';
    while (command != 'e') // if command not e (exit)
    {
        counter++;                                                             // count of files
        cout << "\nWrite command which you want to use (+, -, *, /, ^, %):\n"; // which operator we will use
        cin >> command;
        if (!valid_command(command)) // checkout command in {"+", "-", "*", "/", "^", "%"}
        {
            cout << "ERROR! This command isn't valid\n";
            return -1;
        }
        else
        {
            menu(command);
        }
        cout << "If you want to exit programm writedown 'e'.\n";
        cin >> command;
    }

    return 0;
}