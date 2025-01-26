#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <tuple>

using std::tuple, std::map, std::vector,std::cout, std::string;

#include "file.hpp"

class CSV_File : public File {
    public:

        typedef struct statistics{
                string column_name_;
                tuple<int,string> most_popular_;
                tuple<int,string> least_popular_;

        }statistics;


        explicit CSV_File(string dir) : File(std::move(dir)) {};
        vector<statistics> s_;

        void analyze();
        vector<string> split(string s, const string& delimiter);
         
        statistics stats_;
};
