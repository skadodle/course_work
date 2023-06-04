#include "decoder.h"

int main(int argc, char *argv[])
{
    if (argc == 1) // if we dont get a file
    {
        cout << "Error! Don't have enough arguments to start decode!\n";
        _sleep(5000);
        return -1;
    }
    else if (argc == 2 && !(is_valid_file_name(argv[1])))
    {
        cout << "Error! Isn't valid filename!\n";
        _sleep(5000);
        return -1;
    }
    else if (argc == 3 && (strcmp(argv[1], "-d") == NULL || strcmp(argv[2], "-d") == NULL))
    {
        cout << "DIRECTORY!\n";
        DIR *d;
        struct dirent *dir;
        if (strcmp(argv[1], "-d") == NULL)
            d = opendir(argv[2]); // open directory with name argv[2] (".")
        if (strcmp(argv[2], "-d") == NULL)
            d = opendir(argv[1]); // open directory with name argv[1] (".")
        if (d)
        {
            while ((dir = readdir(d)) != NULL) // null at the end of directory
            {
                if (!(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) && is_valid_file_name(dir->d_name)) // if filename isn't a "." and ".." and valid for start decode
                    decode(dir->d_name);                                                                                   // start of decoding
            }
            closedir(d);
        }
    }
    else if (argc == 2 && is_valid_file_name(argv[1]))
    {
        if (decode(argv[1]) == -1)
        {
            cout << "Error to decode file!\n";
            return -1;
        }
    }
    else
    {
        cout << "ERROR!\n";
        return -1;
    }

    return 0;
}

bool is_valid_file_name(string file_name) // true if filename is valid (regex - "^file[0-9]{0,}.txt")
{
    static const regex r("^file[0-9]{1,}.txt$"); // regular expression
    return regex_match(file_name, r);
}

int decode(string argv_string)
{
    string file_name = argv_string; // filename (file0.txt - ex)
    string temp_string;             // string for read lines from the file
    int counter = 0;                // ordinal number of the file 0, 1, 2, ... etc
    int num = 0;                    // var to translate numbers from the file

    for (int i = 4; i < file_name.size() - 4; i++)
    {
        counter = counter * 10 + int(file_name[i]) - int('0');
    }

    ifstream fin;
    fin.open(file_name); // opening the file for reading

    if (!(fin.is_open())) // file exist(opening correctly)
    {
        cout << "ERROR! Can't open the file: " << file_name << "!\n";
        _sleep(5000);
        return -1;
    }

    ofstream fout;
    fout.open(file_name.erase(file_name.size() - 4) + "_decoded.txt"); // decoded file

    for (int i = 0; i < 3; i++)
    {
        getline(fin, temp_string); // reading line

        for (int j = 0; j < temp_string.size(); j++) // reading the number from the file
        {
            num = num * 10 + int(temp_string[j]) - int('0'); // num = number from file (standart algorithm for number)
        }

        if (i != 2)
        {
            fout << (num ^ 89959085) << endl; // cout in file for first two numbers (operands between which the operator is used)
        }
        else
        {
            fout << char(num - 15 - (2 + counter) % 3) << endl; // cout in file operator
        }
        num = 0;
    }

    fout.close(); // closing the files
    fin.close();
}