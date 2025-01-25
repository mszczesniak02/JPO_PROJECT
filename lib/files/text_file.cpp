#pragma once

#include "file.hpp"
#include "text_file.hpp"

vector<string> TXT_File::split(string& s, string delimiter = " ") {
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
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
        reverse(msg.begin(), msg.end());
    }
    return msg;
};
