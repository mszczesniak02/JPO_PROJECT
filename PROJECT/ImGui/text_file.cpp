#pragma once

#include "file.hpp"
#include "text_file.hpp"

vector<string> TXT_File::split(string& s) { // SPLITS STRING BY  SEPARATOR/DELIMITER
    string delimiter = " ";
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) { // IF SEPARATOR FOUND, SUBSTRING AND APPEND INTO VEC
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
};
 void TXT_File::analyze(){ // REALIZE THE VIRTUAL FUNC
    map<char,int> frequency_letters;
    map<string,int> frequency_words;

    for (int i =0;i < contents_.size(); i++){
        vector<string> line = split(contents_[i]); // GET EACH WORD SEPARATED BY SPACE
        for (auto &element : line) element = remove_white(element); // REMOVE WHITE SPACE AT THE START AND FIN
        
         // LOGIC: IF WORD/LETTER IN MAP, INCREMENT ELSE PUT INTO MAP 
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

    vector<string> freq_lett_char;
    vector<int> freq_lett_int;
    vector<string> freq_word_str;   // TEMPORARY MEASURE, FOR EASIER HANDLING LATER
    vector<int> freq_word_int;


    for (auto const& [key,val] : frequency_letters){
        std::string temp(1,key);

        freq_lett_char.push_back(temp);     // 'TRANSPOSE' THE MAP INTO VECTORS
        freq_lett_int.push_back(val);
    }

    for (auto const& [key,val] : frequency_words){
        freq_word_str.push_back(key);
        freq_word_int.push_back(val);
    }

    // COMBINE 4 INTO 2 VECTORS
    freq_lett_char.insert( freq_lett_char.end(), freq_word_str.begin(), freq_word_str.end() );
    freq_lett_int.insert(  freq_lett_int.end(), freq_word_int .begin(), freq_word_int .end() );


    stats_ = {freq_lett_char,freq_lett_int};   // RETURN RESULT      
    };

// Remove whitespace from the start and end of a string
string TXT_File::remove_white(string msg) {
    if (msg.length() < 1) return msg;
    for (int j = 0; j <= 1; j++) {
        int start = 0;
        for (int i = 0; i < msg.length(); i++) {
            if (msg[i] == ' ' || msg[i] == '\n' || msg[i] == '\t') {
                start++;
            } else break;
        }
        msg = msg.substr(start);
        reverse(msg.begin(), msg.end()); // REVERSE STRING TWICE, MAYBE SLOW, BUT WORKS
    }
    return msg;
};
