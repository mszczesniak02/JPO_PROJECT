#pragma once

#include "file.hpp"

class DEFAULT_File : public File {
public:
    explicit DEFAULT_File(string dir) : File(std::move(dir)) {}
    void analyze() override {
        stats_.msg_ = default_msg_;
    }
    static std::string default_msg_; // HANDLE THE UNSUPPORTED FILE

        
    typedef struct statistics{
            string msg_;
            

    }statistics;

    statistics stats_;

};