#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "file.hpp"

using std::string, std::vector, std::map, std::cout;

class TXT_File : public File {
public:
    explicit TXT_File(string dir) : File(std::move(dir)) {}

    typedef struct statistics{
        vector<string> freq_str_;
        vector<int> freq_int;

        map<char,int> frequency_letters; // USED FOR COUNTING THE APPERANCES OF LETTERS
        map<string,int> frequency_words;// USED FOR COUNTING THE APPERANCES OF WORDS
    }statistics;

    statistics stats_;

   void analyze();

    vector<string> split(string& s); // HELPER FUNCTIONS FOR HANDLING STRINGS
    string remove_white(string msg);

};
