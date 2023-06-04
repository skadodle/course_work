#pragma once

#include <iostream> // in out
#include <string>   // strings

using namespace std; // std::

extern short counter; // ordinal number of file(start from 0)

inline int sum(int, int);      // +
inline int razn(int, int);     // -
inline int multiply(int, int); // *
inline int delen(int, int);    // /
inline int step(int, int);     // ^
inline int ost(int, int);      // %

bool valid_command(char command);                         // checkout command in {"+", "-", "*", "/", "^", "%"}
void send_file(int first_num, int second_num, char oper); // secret_stream for sending ICMP
void menu(char);                                          // switch-case for operators

int icmp(int *arr, char *destination);
int data_length(int *nums, string &str);