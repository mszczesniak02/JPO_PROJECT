#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <tuple>

#include "file.hpp"

using namespace std;

typedef struct Statistics {
    int total_;
    vector<tuple<string, int>> param_;
} Statistics;

class CSS_File : public File {
public:
    explicit CSS_File(string dir) : File(std::move(dir)) {}
    vector<Statistics> result;

    void analyze() override {
        
        
        Statistics class_stats, property_stats, pseudo_stats, media_query_stats;
        detect_classes(class_stats);
        detect_properties(property_stats);
        detect_pseudo_classes( pseudo_stats);
        detect_media_queries(media_query_stats);

        result.push_back(class_stats);
        result.push_back(property_stats);
        result.push_back(pseudo_stats);
        result.push_back(media_query_stats);


    }

    void detect_classes(Statistics& stats);
    void detect_pseudo_classes(Statistics& stats);
    void detect_properties( Statistics& stats);
    void detect_media_queries(Statistics& stats); 
};