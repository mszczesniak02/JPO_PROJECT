#pragma once


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "file.hpp"

using namespace std;


typedef struct statistics{
    map<char,int> frequency_letters;
    map<string,int> frequency_words;
    
}statistics;

class TXT_File : public File {
public:
    explicit TXT_File(string dir) : File(std::move(dir)) {}

    void analyze() override {
        map<char,int> frequency_letters;
        map<string,int> frequency_words;
        for (int i =0;i < contents_.size(); i++){
            vector<string> line = split(contents_[i]);
            for (auto &element : line) element = remove_white(element);
            
            for (auto &word : line) {
                if (frequency_words.find(word) != frequency_words.end()) {
                    frequency_words[word]++;
                } else {
                    frequency_words[word] = 1;
                }
                for (auto &letter : word){
                    if (frequency_letters.find(letter) != frequency_letters.end()) {
                        frequency_letters[letter]++;
                    } else {
                        frequency_letters[letter] = 1;
                    }   
                }
            }
        }
        statistics s = {frequency_letters, frequency_words};
    }
    vector<string> split(string& s, string delimiter = " ");
    string remove_white(string msg);

};
