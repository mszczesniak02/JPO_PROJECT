#pragma once

using namespace std;


#include "html_file.hpp"


vector<string> HTML_File::split(string& s, const string& delimiter) {
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
}

    // Remove whitespace from the start and end of a string
string HTML_File::remove_white(string msg) {
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
}
vector<string> HTML_File::detect_comments(vector<string>& contents_) {
    vector<string> comment_content;
    bool is_inside = false;
    int line_start = 0;

    for (int i = 0; i < contents_.size(); i++) {
        string line = remove_white(contents_[i]);
        
        // Look for the start of a comment
        if (!is_inside && line.find("<!--") != string::npos) {
            is_inside = true;
            int start_index = line.find("<!--");
            // Check if the end of the comment is within the same line
            if (line.find("-->", start_index) != string::npos) {
                comment_content.push_back(remove_white(line.substr(start_index + 4, line.find("-->") - start_index - 4)));
                is_inside = false;
            } else {
                line_start = i;
            }
        }
        // If inside a comment block, check for its end
        else if (is_inside) {
            if (line.find("-->") != string::npos) {
                comment_content.push_back(remove_white(contents_[i].substr(0, contents_[i].find("-->"))));
                is_inside = false;
            } else {
                comment_content.push_back(line);
            }
        }
    }

    return comment_content;
}

HTML_File::temp HTML_File::analyze_html_tags(const vector<string>& contents_) {
    // Refined regex to capture HTML tags (both start and end)
    regex tagRegex("<(/?)([a-zA-Z0-9]+)(\\s*[^>]*?)>");
    map<string, int> tagCount;
    int totalTags = 0;
    int nonTagLines = 0;

    // Loop through the HTML lines
    for (const auto& line : contents_) {
        string trimmedLine = remove_white(line);
        if (trimmedLine.empty()) { // empty line
            nonTagLines++;
            continue;
        }

        // Search for tags in the line
        auto begin = sregex_iterator(trimmedLine.begin(), trimmedLine.end(), tagRegex);
        auto end = sregex_iterator();

        //matched tags
        for (auto i = begin; i != end; ++i) {
            string tag = (*i)[2].str();                 // Tag name (without the < or /)
            bool isClosingTag = (*i)[1].matched;        // If it's a closing tag (contains '/')
                                                        // Count the tag if it's an opening tag
            if (!isClosingTag) {                         // If it's not a void tag, count it
                if (voidTags.find(tag) == voidTags.end()) tagCount[tag]++;
            }
            totalTags++;
        }
    }
    return {totalTags,nonTagLines };

};