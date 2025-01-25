#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <regex>
#include "file.hpp"


class HTML_File : public File {
public:
    typedef struct statistics{
                int total_tags;
                int non_tag_lines;
                vector<string> comments_;

    }statistics;

    typedef struct temp{
        int total_tags;
        //tuple<int,string> most_popular_;
        int non_tag_lines;

    }temp;

    explicit HTML_File(string dir) : File(std::move(dir)) {}
    
    void HTML_File::analyze() override {
      
        vector<string> comments = detect_comments(contents_);

       
        temp st = analyze_html_tags(contents_);

        statistics result = {st.total_tags, st.non_tag_lines ,comments};

        for (auto & com: result.comments_){
            cout<<com<<endl;
        }
    };
    const map<string, bool> HTML_File::voidTags = {
        {"area", true}, {"base", true}, {"br", true}, {"col", true},
        {"embed", true}, {"hr", true}, {"img", true}, {"input", true},
        {"link", true}, {"meta", true}, {"source", true}, {"track", true}, {"wbr", true}
    };
    vector<string> split(string& s, const string& delimiter);

   
    string remove_white(string msg); // Remove whitespace from the start and end of a string
    vector<string> detect_comments(vector<string>& contents_);
    

    temp analyze_html_tags(const vector<string>& contents_);
};

