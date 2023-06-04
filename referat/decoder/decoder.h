#pragma once

#include <iostream>    // in out
#include <string>      // strings
#include <fstream>     // files
#include "dirent.h"    // directory
#include <sys/types.h> // for directory
#include <regex>       // regular expressions

using namespace std; // std::

bool is_valid_file_name(string file_name); // true if filename is valid (regex - "^file[0-9]{0,}.txt")
int decode(string argv_string);            // func for decoding files