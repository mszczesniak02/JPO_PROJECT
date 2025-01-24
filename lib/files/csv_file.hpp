#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <tuple>

using std::tuple, std::map, std::vector,std::cout;

#include "file.hpp"

typedef struct statistics{
        string column_name_;
        tuple<int,string> most_popular_;
        tuple<int,string> least_popular_;

}statistics;


class CSV_File : public File {
    public:

        explicit CSV_File(string dir) : File(std::move(dir)) {};
        vector<statistics> stats_;

        void analyze() override;
};
