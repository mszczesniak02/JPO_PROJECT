#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using   std::vector, std::string, std::fstream, std::cout;

typedef struct Properties{         // basic file's properties, supposed to mimic the Windows' file properties menu
    string dir_absolute_;
    string extention_;
    string size_;
    bool is_dir_;
    bool perms_;
}Properties;


class File{ // base class, read file into vector and close the file 
    protected:
        Properties properties_;     // basic file properties, struct 'Properties' declaration above
        string dir_;                // path to analyze
        vector<string> contents_;   // main file storage unit

    public:
        explicit File(string dir);
        virtual ~File() = default;

        // class funcs tools 
        void print_error(string error_msg);
        static unsigned int total_files_opened_; 
        
        // file get contect
        string get_dir();
        vector<string>& get_contents();
        
        // file properties
        Properties& get_file_properties(); 
        void file_properties(); // date, owner, last modification, size, read-only 
        void print_file_properties();

        // file analyzer
        virtual void analyze() = 0; // different file types have different ways to analyze themselves, so this is purely for convinience 
        
};
